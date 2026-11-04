#include <pthread.h>

struct station {
    pthread_mutex_t lock;

    pthread_cond_t car_available;
    pthread_cond_t passenger_event;

    int waiting_passengers;
    int available_seats;
    int passengers_boarding;
    int passengers_boarded;
    int passengers_expected;
    int car_present;
    int car_generation;
    int passengers_to_authorize;
};


void station_init(struct station *station) {

    pthread_mutex_init(&station->lock, NULL);

    pthread_cond_init(&station->car_available, NULL);
    pthread_cond_init(&station->passenger_event, NULL);

    station->waiting_passengers = 0;
    station->available_seats = 0;
    station->passengers_boarding = 0;
    station->passengers_boarded = 0;
    station->passengers_to_authorize = 0;
    station->car_present = 0;
    station->car_generation = 0;
}


//pthread_mutex_lock(&station->lock);

void station_load_car(struct station *station, int count) {

    pthread_mutex_lock(&station->lock);

    station->available_seats = count;

    station->passengers_expected =station->waiting_passengers < count ? station->waiting_passengers : count;

    station->passengers_boarded = 0;

    station->passengers_to_authorize = station->passengers_expected;

    station->car_generation++;

    pthread_cond_broadcast(&station->car_available);

    while (station->passengers_boarded < station->passengers_expected) {

        pthread_cond_wait(&station->passenger_event, &station->lock);
    }

    pthread_mutex_unlock(&station->lock);
}

void station_wait_for_car(struct station *station){
    pthread_mutex_lock(&station->lock);

    int my_generation = station->car_generation;

    station->waiting_passengers++;

    while (my_generation == station->car_generation || station->passengers_to_authorize == 0) {
            pthread_cond_wait(&station->car_available,&station->lock);
    }

    station->waiting_passengers--;
    station->available_seats--;
    station->passengers_to_authorize--;

    pthread_mutex_unlock(&station->lock);
}

//station->available_seats--;

//pthread_mutex_unlock(&station->lock);

//passengers_expected = MIN(waiting_passengers, free_seats);