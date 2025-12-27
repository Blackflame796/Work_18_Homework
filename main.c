#include <stdio.h>
#include <string.h>

#define FLIGHT_COUNT 5

struct Time {
    int hour;
    int minute;
};

struct Flight {
    int number;           // Номер авиарейса
    struct Time start_time; // Время вылета
    struct Time end_time;   // Время прилета
    char destination[100];  // Направление
    char aircraft[50];     // Марка самолета
    float distance;        // Расстояние в км
    float speed;           // Cкорость
};

// Функция для вычисления времени в пути
float calculate_time(struct Time dep, struct Time arr) {
    float hours = arr.hour - dep.hour;
    float minutes = arr.minute - dep.minute;
    return hours + minutes / 60.0; // в часах
}

int main() {
    struct Flight flights[FLIGHT_COUNT];
    struct Flight *fastest;
    char buffer[100];  // Буфер для ввода
    
    for (int i = 0; i < FLIGHT_COUNT; i++) {
        printf("\n=== Ввод данных авиарейса %d ===\n\n", i + 1);
        
        printf("Номер авиарейса: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &flights[i].number);
        
        printf("Время вылета (часы минуты): ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d %d", &flights[i].start_time.hour, &flights[i].start_time.minute);
        
        printf("Время прилета (часы минуты): ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d %d", &flights[i].end_time.hour, &flights[i].end_time.minute);
        
        printf("Направление: ");
        fgets(flights[i].destination, 50, stdin);
        // Удаление символа перехода на новую строку
        int len_destination = strlen(flights[i].destination);
        if (len_destination > 0 && flights[i].destination[len_destination-1] == '\n') {
            flights[i].destination[len_destination-1] = '\0';
        }
        
        printf("Марка самолета: ");
        fgets(flights[i].aircraft, 30, stdin);
        // Удаление символа перехода на новую строку
        int len_aircraft = strlen(flights[i].aircraft);
        if (len_aircraft > 0 && flights[i].aircraft[len_aircraft-1] == '\n') {
            flights[i].aircraft[len_aircraft-1] = '\0';
        }
        
        printf("Расстояние (км): ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%f", &flights[i].distance);
        
        float duration = calculate_time(flights[i].start_time, flights[i].end_time);
        if (duration > 0) {
            flights[i].speed = flights[i].distance / duration;
        } else {
            // Если время прилёта меньше времени вылета, тогда прибавляем 24 часа, так как уже прилёт на следующий день
            duration += 24;
            flights[i].speed = flights[i].distance / duration;
        }
    }
    
    fastest = &flights[0];
    for (int i = 1; i < FLIGHT_COUNT; i++) {
        if (flights[i].speed > fastest->speed) {
            fastest = &flights[i];
        }
    }
    
    printf("\nАвиарейс с максимальной скоростью:\n\n");
    printf("Номер авиарейса: %d\n", fastest->number);
    printf("Время вылета: %02d:%02d\n", fastest->start_time.hour, fastest->start_time.minute);
    printf("Время прилета: %02d:%02d\n", fastest->end_time.hour, fastest->end_time.minute);
    printf("Направление: %s\n", fastest->destination);
    printf("Марка самолета: %s\n", fastest->aircraft);
    printf("Расстояние: %.1f км\n", fastest->distance);
    printf("Скорость: %.1f км/ч\n", fastest->speed);
    
    return 0;
}