/* Includes ------------------------------------------------------------------*/
#include "network.h"
#include "core/net.h"
#include "dhcp/dhcp_client.h"
#include "drivers/enc28j60.h"
#include "drivers/spi_driver.h"
#include "drivers/ext_int_driver.h"
#include "configs.h"
#include "uuid.h"
#include "xprintf.h"
#include "log.h"
#include "httpd.h"
/* User's defines ------------------------------------------------------------*/
#define APP_MAC_ADDR_LEN 18
 
register_defalt_config( "{\"ipv4\":{\"useipv4\":true,\"usedhcp\":true,\"address\":\"192.168.1.211\",\"netmask\":\"255.255.255.0\",\"gateway\":\"192.168.1.1\",\"primarydns\":\"192.168.1.1\",\"secondarydns\":\"8.8.8.8\"},\"ipv6\":{\"useipv6\":false,\"useslaac\":false,\"linklocaladdress\":\"fe80::107\",\"ipv6prefix\":\"2001:db8::\",\"ipv6prefixlength\":64,\"ipv6globaladdress\":\"2001:db8::107\",\"ipv6router\":\"fe80::1\",\"ipv6primarydns\":\"2001:4860:4860::8888\",\"ipv6secondarydns\":\"2001:4860:486\"}}");


/* Variables -----------------------------------------------------------------*/
typedef struct
{
  
   bool_t useIpV4;
   bool_t useDhcp;
   bool_t useIpV6;
   bool_t needSave;
   Ipv4Addr ipv4Addr;
   Ipv4Addr ipv4Mask;
   Ipv4Addr ipv4Gateway;
   Ipv4Addr ipv4Dns1;
   Ipv4Addr ipv4Dns2;
   char sMacAddr[APP_MAC_ADDR_LEN];
   MacAddr macAddr;
   char hostname[NET_MAX_HOSTNAME_LEN];

} networkContext_t;

static networkContext_t networkContext;
static NetInterface *interface;
static DnsSdService DnsSdServices[1];

//Check TCP/IP stack configuration
#if (IPV4_SUPPORT == ENABLED)

#if (AUTO_IP_SUPPORT == ENABLED)

AutoIpSettings autoIpSettings;
AutoIpContext autoIpContext;

#endif          //AUTO_IP_SUPPORT

#if (DHCP_CLIENT_SUPPORT == ENABLED)

DhcpClientSettings dhcpClientSettings;
DhcpClientCtx dhcpClientContext;

#endif          //DHCP_CLIENT_SUPPORT
#endif          //IPV4_SUPPORT



#if (IPV6_SUPPORT == ENABLED)

static Ipv6Addr ipv6Addr;

#if (SLAAC_SUPPORT == ENABLED)

SlaacSettings slaacSettings;
SlaacContext slaacContext;

#endif //SLAAC_SUPPORT
#endif //IPV6_SUPPORT

#if (DNS_SD_SUPPORT == ENABLED)

DnsSdContext dnsSdContext;
DnsSdSettings dnsSdSettings;

#endif

#if (MDNS_CLIENT_SUPPORT == ENABLED | MDNS_RESPONDER_SUPPORT == ENABLED)

MdnsResponderContext mdnsResponderContext;
MdnsResponderSettings mdnsResponderSettings;

#endif

/* Function prototypes -------------------------------------------------------*/
static error_t networkConfigure (void);
static error_t parseNetwork(jsmnParserStruct * jsonParser, configMode mode);
static error_t useDefaultMacAddress(void);
static error_t useDefaultHostName(void);
static error_t networkStart(void);
static uint8_t parseIpv4Config(jsmnParserStruct * jsonParser);

static error_t networkConfigure (void)
{
   error_t error;
   error = read_default(&defaultConfig, &parseNetwork);

   error = read_config("/config/lan.json",&parseNetwork);
   return error;
}

static error_t parseNetwork(jsmnParserStruct * jsonParser, configMode mode)
{
   int strLen;
   jsmn_init(jsonParser->jSMNparser);
   networkContext.needSave = FALSE;
   //   networkContext.useIpV4 = FALSE;
   //   networkContext.useIpV6 = FALSE;
   //   networkContext.useDhcp = FALSE;
   jsonParser->resultCode = xjsmn_parse(jsonParser);

   strLen = jsmn_get_string(jsonParser, "$.mac", &networkContext.sMacAddr[0], APP_MAC_ADDR_LEN);
   if (strLen == 0)
   {
      useDefaultMacAddress();
   }

   strLen = jsmn_get_string(jsonParser, "$.hostname", &networkContext.hostname[0], NET_MAX_HOSTNAME_LEN);
   if (strLen == 0)
   {
      useDefaultHostName();
   }

   jsmn_get_bool(jsonParser, "$.ipv4.useipv4", &networkContext.useIpV4);
   if (networkContext.useIpV4 == TRUE)
   {
      parseIpv4Config(jsonParser);
   }

#if IPV6_SUPPORT == ENABLED
   networkContext.useIpV6 = jsmn_get_bool(data, jSMNtokens, resultCode, "$.ipv6.useipv6");
   if (networkContext.useIpV6 == TRUE)
   {
      if (strncmp (&data[jSMNtokens[tokNum].start], "true" ,4) == 0)
      {
         if (parseIpv6Config(data, jSMNtokens, resultCode)!=5)
            ipv6_use_default_configs();
      }

   }
   if (ipEnable == 0)
   {
      ipv4UseDefaultConfigs();
      ipv6_use_default_configs();
   }
#endif

   jsmn_get_bool(jsonParser, "$.needSave", &networkContext.needSave);

   return NO_ERROR;
}

void NetworkTask(void const *argument)
{
    (void)argument;
    configInit();

    // sensorsConfigure();
    // logicConfigure();

    networkConfigure();

    //   executorsConfigure();
    // ntpdConfigure();
    // clockConfigure();

#if (FTP_SERVER_SUPPORT == ENABLED)
    // ftpdConfigure();
#endif
    httpdConfigure();

    configDeinit();

    // logicStart();
    networkStart();
    // ntpdStart();

#if (FTP_SERVER_SUPPORT == ENABLED)
    // ftpdStart();
#endif
    httpdStart();

    //   vTaskDelay(1000);

    vTaskDelete(NULL);
}

static error_t useDefaultMacAddress(void)
{
   error_t error;
   sprintf(networkContext.sMacAddr, "10-00-00-%X-%X-%X", uuid->b[9], uuid->b[10], uuid->b[11]);
   error = macStringToAddr(&(networkContext.sMacAddr[0]), &networkContext.macAddr);
   return error;
}

static error_t useDefaultHostName(void)
{
   sprintf(networkContext.hostname, "aurora-%X-%X-%X", uuid->b[9], uuid->b[10], uuid->b[11]);
   return NO_ERROR;
}

static error_t networkStart(void)
{

   error_t error; //for debugging
   char name[NET_MAX_HOSTNAME_LEN + 9];
   char *aurora = "aurora - ";
   char *pHostname = &(networkContext.hostname[0]);
   char *pName  = &name[0];

   xprintf("Starting TCP/IP stack\r\n");

   error = netInit();
   interface = &netInterface[0];

   //Set interface name
   netSetInterfaceName(interface, "eth0");
   //Set host name
   netSetHostname(interface, pHostname);
   //Select the relevant network adapter
   netSetDriver(interface, &enc28j60Driver);
   //Underlying SPI driver
   netSetSpiDriver(interface, &spiDriver);
   //Set external interrupt line driver
   netSetExtIntDriver(interface, &extIntDriver);

   netSetMacAddr(interface, &networkContext.macAddr);
 
   error = netConfigInterface(interface);


    if (networkContext.useDhcp == TRUE)
    {
      //Get default settings
      dhcpClientGetDefaultSettings(&dhcpClientSettings);
      //Set the network interface to be configured by DHCP
      dhcpClientSettings.interface = interface;
      //Disable rapid commit option
      dhcpClientSettings.rapidCommit = FALSE;

      //DHCP client initialization
      LOG_INFO("Initializing DHCP client... ");
      error = dhcpClientInit(&dhcpClientContext, &dhcpClientSettings);
      //Failed to initialize DHCP client?
      LOG_STATUS(error);

      //Start DHCP client
      LOG_INFO("Starting DHCP client... ");
      error = dhcpClientStart(&dhcpClientContext);
      //Failed to start DHCP client?
      LOG_STATUS(error);
    }
   else
   {
      //Set IPv4 host address

      error = ipv4SetHostAddr(interface, networkContext.ipv4Addr);
      if (error)
         return error;
      error = ipv4SetSubnetMask(interface, networkContext.ipv4Mask);
      if (error)
         return error;
      error = ipv4SetDefaultGateway(interface, networkContext.ipv4Gateway);
      if (error)
         return error;
      error = ipv4SetDnsServer(interface, 0, networkContext.ipv4Dns1);
      if (error)
         return error;
      error = ipv4SetDnsServer(interface, 1, networkContext.ipv4Dns2);
      if (error)
         return error;

   }


#if (MDNS_RESPONDER_SUPPORT == ENABLED)
   //Get default settings
   mdnsResponderGetDefaultSettings(&mdnsResponderSettings);
   //Underlying network interface
   mdnsResponderSettings.interface = &netInterface[0];

   //mDNS responder initialization
   LOG_INFO("Initializing mDNS responder... ");
   error = mdnsResponderInit(&mdnsResponderContext, &mdnsResponderSettings);
   //Failed to initialize mDNS responder?
   LOG_STATUS(error);

   //Set mDNS hostname
   LOG_INFO("Setting hostname to \"%s\"... ", pHostname);
   error = mdnsResponderSetHostname(&mdnsResponderContext, pHostname);
   //Any error to report?
   LOG_STATUS(error);

   //Start mDNS responder
   LOG_INFO("Starting mDNS responder... ");
   error = mdnsResponderStart(&mdnsResponderContext);
   //Failed to start mDNS responder?
   LOG_STATUS(error);

#endif
#if (DNS_SD_SUPPORT == ENABLED)
   //Get default settings
   dnsSdGetDefaultSettings(&dnsSdSettings);
   //Underlying network interface
   dnsSdSettings.interface = &netInterface[0];

   //DNS-SD initialization
   LOG_INFO("Initializing DNS-SD... ");
   error = dnsSdInit(&dnsSdContext, &dnsSdSettings);
   //Failed to initialize DNS-SD?
   LOG_STATUS(error);

   //Unregister service
   error = dnsSdUnregisterService(&dnsSdContext, "_http._tcp");
   error = dnsSdUnregisterService(&dnsSdContext, "_ftp._tcp");

   strcpy(name, aurora);
   strcat(name, pHostname);

   //Set instance name
   LOG_INFO("Setting instance name to \"%s\"... ", pName);
   error = dnsSdSetInstanceName(&dnsSdContext, pName);

   //Any error to report?
   LOG_STATUS(error);

   //Register DNS-SD service
   error = dnsSdRegisterService(&dnsSdContext,
      "_http._tcp",
      0,
      0,
      80,
      "txtvers=1;"
      "path=/");

   error = dnsSdRegisterService(&dnsSdContext,
      "_ftp._tcp",
      0,
      0,
      21,
      "");

   //Start DNS-SD
   LOG_INFO("Starting DNS-SD... ");
   error = dnsSdStart(&dnsSdContext);
   //Failed to start DNS-SD?
   LOG_STATUS(error);
   
#endif
   return NO_ERROR;
}

static uint8_t parseIpv4Config(jsmnParserStruct * jsonParser)
{
   error_t error;
#define IP_MAX_LEN 16 //Includeing '\0' at end
   char ipAddr[] = {"xxx.xxx.xxx.xxx\0"};
   char ipMask[] = {"xxx.xxx.xxx.xxx\0"};
   char ipGateway[] = {"xxx.xxx.xxx.xxx\0"};
   char ipDns1[] = {"xxx.xxx.xxx.xxx\0"};
   char ipDns2[] = {"xxx.xxx.xxx.xxx\0"};
   static Ipv4Addr testIpAddres;
   int length;
#if (IPV4_SUPPORT == ENABLED)

   jsmn_get_bool(jsonParser, "$.ipv4.usedhcp", &networkContext.useDhcp);

   length = jsmn_get_string(jsonParser, "$.ipv4.address", &ipAddr[0], IP_MAX_LEN);
   if (length ==0 || length > IP_MAX_LEN)
   {
      xprintf("Warning: wrong ip address in config file \"/config/lan.json\" ");
   }
   length = jsmn_get_string(jsonParser, "$.ipv4.netmask", &ipMask[0], IP_MAX_LEN);
   if (length ==0 || length > IP_MAX_LEN)
   {
      xprintf("Warning: wrong subnet mask in config file \"/lan.json\" ");
   }

   length = jsmn_get_string(jsonParser, "$.ipv4.gateway", &ipGateway[0], IP_MAX_LEN);
   if (length ==0 || length > IP_MAX_LEN)
   {
      xprintf("Warning: wrong default gateway in config file \"/config/lan.json\" ");
   }

   length = jsmn_get_string(jsonParser, "$.ipv4.primarydns", &ipDns1[0], IP_MAX_LEN);
   if (length ==0 || length > IP_MAX_LEN)
   {
      xprintf("Warning: wrong primary dns in config file \"/config/lan.json\" ");
   }

   length = jsmn_get_string(jsonParser, "$.ipv4.secondarydns", &ipDns2[0], IP_MAX_LEN);

   if (length ==0 || length > IP_MAX_LEN)
   {
      xprintf("Warning: wrong primary dns in config file \"/config/lan.json\" ");
   }

#endif
   //Check addresses
   error = ipv4StringToAddr(&ipAddr[0], &testIpAddres);
   if (error == NO_ERROR)
      error = ipv4StringToAddr(&ipMask[0], &testIpAddres);
   if (error == NO_ERROR)
      error = ipv4StringToAddr(&ipGateway[0], &testIpAddres);

   if (error == NO_ERROR)
   {
      ipv4StringToAddr(&ipAddr[0], &networkContext.ipv4Addr);
      ipv4StringToAddr(&ipMask[0], &networkContext.ipv4Mask);
      ipv4StringToAddr(&ipGateway[0], &networkContext.ipv4Gateway);
   }
   ipv4StringToAddr(&ipDns1[0], &networkContext.ipv4Dns1);
   ipv4StringToAddr(&ipDns2[0], &networkContext.ipv4Dns2);

   return error;
}