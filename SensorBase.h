#if defined(DEBUG)
#define DBEGIN(baud)    Serial.begin(baud);
#define DFLUSH()        Serial.flush()
#define DPRINT(data)    Serial.print(data)
#define DPRINTLN(data)  Serial.println(data)
#else
#define DBEGIN(baud)    power_usart0_disable();
#define DFLUSH()        
#define DPRINT(data)    
#define DPRINTLN(data)  
#endif

#define SERVER_ADDRESS RH_BROADCAST_ADDRESS
#define SERIAL_BAUD 9600

// Arduino Node Sensor Pinout
#define PIN_DS18S20    3
#define PIN_MPX_POWER  8
#define PIN_MPX_ADC    0
#define PIN_SHT_DATA   4
#define PIN_SHT_SCK    5
#define PIN_LED1       3
#define PIN_LED2       2
#define PIN_POWER_EN   7
#define PIN_RFM_INT    2
#define PIN_RFM_SS     10


typedef struct {
  uint8_t      command;
  s_temp      temp;
  s_hum       hum;
  s_lux       lux;
  s_volt      battery;
  s_lowbat    lowbat;
  s_io_analog moisture;
} Payload;
