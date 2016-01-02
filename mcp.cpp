#include "mcp.h"

uint8_t MCP::getMode(void) {
	return mode;
}

void MCP::init(uint8_t enable_pin) {
	MCP::enable_pin = enable_pin;
	pinMode(enable_pin, OUTPUT);
	disablePowerBoost();
}

void MCP::setMinVoltage(float voltage) {
	MCP::min_voltage = voltage;
}

void MCP::disablePowerBoost(void) {
	digitalWrite(enable_pin, LOW);
}

void MCP::enablePowerBoost(void) {
	digitalWrite(enable_pin, HIGH);
}

void MCP::sleep(void) {
	// wenn nicht always on, dann vor dem schlafen deaktivieren
	if(mode == POWER_MODE_ONDEMAND) {
		serial.println("Disable power before sleep!");
		disablePowerBoost();
	}
}

void MCP::checkMode(float currentVoltage) {
	
	if(currentVoltage <= POWER_SUPPLY_AVR_MIN) {
		// level selbst für avr zu niedrig, nun immer an lassen
		serial.println("Switch PB to Always on");
		enablePowerBoost();
		mode = POWER_MODE_ALWAYS_ON;

	} else if(currentVoltage < min_voltage) {
		// level für sensoren zu niedrig, für messung an
		serial.println("Switch PB to on demand");
		enablePowerBoost();
		mode = POWER_MODE_ONDEMAND;

	} else {
		// versorgung hoch genung, aus lassen
		serial.println("Switch PB to passtru");
		disablePowerBoost();
		mode = POWER_MODE_PASSTRU;

	}
	
}
