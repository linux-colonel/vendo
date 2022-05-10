#include <Arduino.h>
#include <SPIFFS.h>

#include "config.h"

#include "multiball.h"
#include <multiball/app.h>
#include <multiball/homebus.h>

#include "leds.h"
#include "presets.h"
#include "animations.h"
#include "http_server.h"

#include "vendo.h"

#include <multiball/bme280.h>

#include "hw.h"

MultiballApp App;

void setup() {

  delay(500);


  App.begin("discoball");

  http_server_setup();
  Serial.println("[http_server]");

  static const char *ro_ddcs[] = {
                      DDC_AIR_SENSOR,
		      DDC_LED_UPDATE,
		      DDC_LED_CONFIG,
		      DDC_LED_PRESETS,
		      DDC_LED_ANIMATIONS,
                      DDC_SYSTEM,
                      DDC_DIAGNOSTIC,
                      NULL
  };
  static const char *wo_ddcs[] = { NULL };
  static char mac_address[3*6];

  strncpy(mac_address, App.mac_address().c_str(), 3*6);

  // this is... wrong - needs to be sorted for proper Homebus use
  homebus_configure("Homebus",
                    "Vendo LED Controller",
                    mac_address,
                    "",
                    ro_ddcs,
                    wo_ddcs);

  homebus_setup();
  Serial.println("[homebus]");

  App.handle();
  delay(250);
  App.handle();

  leds_setup();
  Serial.println("[leds]");

  preset_setup();
  Serial.println("[presets]");

  animation_setup();
  Serial.println("[animations]");

  bme280_setup();
  Serial.println("[bme280]");

  vendo_setup();
  Serial.println("[vendo]");
}

void loop() {
  App.handle();

  vendo_handle();

  http_server_handle();

  leds_handle();

  bme280_handle();
}
