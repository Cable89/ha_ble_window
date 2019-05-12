#ifndef WINDOW_H
#define WINDOW_H

#define DIR_RELAY_PIN 16    // P0.16
#define POWER_RELAY_PIN 11  // P0.11
#define DIR_OPEN 1
#define DIR_CLOSE 0
#define OPENING_DURATION 10000 // milliseconds needed to go from fully closed to fully open
#define CLOSING_DURATION 10000 // milliseconds needed to go from fully open to fully closed
#define WINDOW_TRAVEL_LENGTH 255 // one byte resolution from fully closed (0) to fully open (255)

void window_open(void);
void window_close(void);
void window_actuate(uint8_t dir, uint16_t duration);
void window_set_position(uint8_t position);
uint8_t get_window_position(void);

#endif //WINDOW_H