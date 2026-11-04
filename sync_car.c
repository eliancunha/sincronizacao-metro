#include <pthread.h>

struct station {
    pthread_mutex_t lock;

    pthread_cond_t car_available;
    pthread_cond_t passenger_event;

    int waiting_passengers;
    int available_seats;
    int passengers_boarding;
    int car_present;
};

