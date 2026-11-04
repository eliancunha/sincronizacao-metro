
#ifndef SYNC_CAR_H
#define SYNC_CAR_H

#include <pthread.h>

struct station {
    pthread_mutex_t lock;

    pthread_cond_t car_available;
    pthread_cond_t passenger_event;

    int waiting_passengers;
    int available_seats;
    int passengers_boarded;
    int passengers_expected;
    int car_generation;
    int passengers_to_authorize;
};

void station_init(struct station *station);
void station_load_car(struct station *station, int count);
void station_wait_for_car(struct station *station);
void station_on_board(struct station *station);

#endif
