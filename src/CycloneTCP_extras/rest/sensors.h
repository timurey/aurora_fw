/*
 * sensors.h
 *
 *  Created on: 25 июня 2015 г.
 *      Author: timurtaipov
 */

#ifndef MY_CYCLONE_REST_SENSORS_H_
#define MY_CYCLONE_REST_SENSORS_H_


#include "error.h"
#include "rest.h"
#include "onewire_conf.h"
#include "os_port.h"
#include "compiler_port.h"
#include "../../driver/include/DriverInterface.h"


#define MAX_ONEWIRE_COUNT 16

#define SENSORS_HEALTH_MAX_VALUE 100
#define SENSORS_HEALTH_MIN_VALUE 0

typedef enum {
   S_INPUT, //Any input
   S_DOOR, // Door sensor, V_TRIPPED, V_ARMED
   S_MOTION,  // Motion sensor, V_TRIPPED, V_ARMED
   S_SMOKE,  // Smoke sensor, V_TRIPPED, V_ARMED
   S_LIGHT, // Binary light or relay, V_STATUS (or V_LIGHT), V_WATT
   S_BINARY, // Binary light or relay, V_STATUS (or V_LIGHT), V_WATT (same as S_LIGHT)
   S_DIMMER, // Dimmable light or fan device, V_STATUS (on/off), V_DIMMER (dimmer level 0-100), V_WATT
   S_COVER, // Blinds or window cover, V_UP, V_DOWN, V_STOP, V_DIMMER (open/close to a percentage)
   S_TEMP, // Temperature sensor, V_TEMP
   S_HUM, // Humidity sensor, V_HUM
   S_BARO, // Barometer sensor, V_PRESSURE, V_FORECAST
   S_WIND, // Wind sensor, V_WIND, V_GUST
   S_RAIN, // Rain sensor, V_RAIN, V_RAINRATE
   S_UV, // Uv sensor, V_UV
   S_WEIGHT, // Personal scale sensor, V_WEIGHT, V_IMPEDANCE
   S_POWER, // Power meter, V_WATT, V_KWH
   S_HEATER, // Header device, V_HVAC_SETPOINT_HEAT, V_HVAC_FLOW_STATE, V_TEMP
   S_DISTANCE, // Distance sensor, V_DISTANCE
   S_LIGHT_LEVEL, // Light level sensor, V_LIGHT_LEVEL (uncalibrated in percentage),  V_LEVEL (light level in lux)
   S_ARDUINO_NODE, // Used (internally) for presenting a non-repeating Arduino node
   S_ARDUINO_REPEATER_NODE, // Used (internally) for presenting a repeating Arduino node
   S_LOCK, // Lock device, V_LOCK_STATUS
   S_IR, // Ir device, V_IR_SEND, V_IR_RECEIVE
   S_WATER, // Water meter, V_FLOW, V_VOLUME
   S_WATER_LEVEL, // Water level, V_FLOW, V_VOLUME
   S_AIR_QUALITY, // Air quality sensor, V_LEVEL
   S_CUSTOM, // Custom sensor
   S_MORZE, //Secuential sensor, like Morze
   S_DUST, // Dust sensor, V_LEVEL
   S_SCENE_CONTROLLER, // Scene controller device, V_SCENE_ON, V_SCENE_OFF.
   S_RGB_LIGHT, // RGB light. Send color component data using V_RGB. Also supports V_WATT
   S_RGBW_LIGHT, // RGB light with an additional White component. Send data using V_RGBW. Also supports V_WATT
   S_COLOR_SENSOR,  // Color sensor, send color information using V_RGB
   S_HVAC, // Thermostat/HVAC device. V_HVAC_SETPOINT_HEAT, V_HVAC_SETPOINT_COLD, V_HVAC_FLOW_STATE, V_HVAC_FLOW_MODE, V_TEMP
   S_MULTIMETER, // Multimeter device, V_VOLTAGE, V_CURRENT, V_IMPEDANCE
   S_SPRINKLER,  // Sprinkler, V_STATUS (turn on/off), V_TRIPPED (if fire detecting device)
   S_WATER_LEAK, // Water leak sensor, V_TRIPPED, V_ARMED
   S_SOUND, // Sound sensor, V_TRIPPED, V_ARMED, V_LEVEL (sound level in dB)
   S_VIBRATION, // Vibration sensor, V_TRIPPED, V_ARMED, V_LEVEL (vibration in Hz)
   S_MOISTURE, // Moisture sensor, V_TRIPPED, V_ARMED, V_LEVEL (water content or moisture in percentage?)
   S_ERROR, //Wrong sensor
   MYSENSOR_ENUM_LEN // Contain length of enum
} mysensor_sensor_t;

typedef struct
{
   const  mysensor_sensor_t type;
   const char * string;
} mysensorSensorList_t;


// Type of sensor data (for set/req/ack messages)
typedef enum {
   D_NONE,
   D_ONEWIRE,
   D_INPUT,
   D_HTTP
} mysensor_driver_t;

typedef union
{
   float fVal;
   uint16_t   uVal;
   char  cVal;
   char  *pVal;
} sensValue_t;

typedef  struct
{
   uint8_t value;
   uint8_t counter;
} __attribute__((__packed__)) health_t;




typedef struct {
   char *ptr;
   int counter;
   char place[];
} PlaceListT;

typedef struct {
   char *ptr;
   int counter;
   char name[];
} NameListT;

typedef struct {
   char *ptr;
   int counter;
   char id[];
} IDListT;

typedef struct
{
   mysensor_sensor_t type; //Not unique
   char* place;   //Place Not unique
   char* name;    //Name Not unique
   char* id;  //Path Unique
   health_t health;
}sensor_t;

typedef struct {
   sensor_t *ptr;
   sensor_t sensor;
} SensorListT;

typedef enum {
   SEARCH_BY_TYPE,
   SEARCH_BY_PLACE,
   SEARCH_BY_NAME,
   SEARCH_BY_ID,
   SEARCH_BY_HEALTH
} byT;
typedef struct {
   byT by;
   void * value;
} searchSensorBy_t;
//typedef enum
//{
//   FLOAT,
//   UINT16,
//   CHAR,
//   PCHAR
//} sensValueType_t;






extern const mysensorSensorList_t sensorList[];
//extern char places[MAX_PLACES_COUNT];
//extern char names[MAX_NAMES_COUNT];
extern char *pPlaces;
extern char *pNames;


error_t restInitSensors(void);
error_t restDenitSensors(void);
error_t restGetSensors(HttpConnection *connection, RestApi_t* RestApi);
error_t restPostSensors(HttpConnection *connection, RestApi_t* RestApi);
error_t restPutSensors(HttpConnection *connection, RestApi_t* RestApi);
error_t restDeleteSensors(HttpConnection *connection, RestApi_t* RestApi);

error_t sensorsGetValue(const char *name, double * value);

IDListT* sensorsFindDeviceId(char * device);
IDListT* addDeviceId(const char * device);
NameListT *sensorsFindName(char * name);
NameListT *sensorsAddName(const char * name);
PlaceListT *  sensorsFindPlace(char * place);
PlaceListT *  sensorsAddPlace(const char * place);
void sensorsConfigure(void);



error_t serialStringToHex(const char *str, size_t length, uint8_t *serial, size_t expectedLength);
char *serialHexToString(const uint8_t *serial, char *str, int length);



#endif /* MY_CYCLONE_REST_SENSORS_H_ */
