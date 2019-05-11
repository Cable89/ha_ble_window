#ifndef WINDOW_H
#define WINDOW_H

void create_timers(void);
void single_shot_timer_handler(void * p_context)

void window_open(void);
void window_close(void);
void window_actuate(uint8_t dir);

#endif //WINDOW_H