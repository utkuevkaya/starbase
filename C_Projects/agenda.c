#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Event
{
    int day, month, year;
    char title[100];
    char description[200];
} Event;

int menu();
void init_events();
void add_event();
void list_events();
void delete_event();
void update_file();
void show_description();
Event *sort_events();

int count = 0;
int capacity = 2;
Event *events;
FILE *file;

int main()
{
    init_events();

    while (1)
    {
        switch (menu())
        {
            case 1:
                add_event();
                update_file();
                break;
            case 2:
                list_events(events);
                break;
            case 3:
                show_description();
                break;
            case 4:
                Event *sorted = sort_events(events);
                list_events(sorted);
                free(sorted);
                break;
            case 5:
                delete_event();
                update_file();
                break;
            case 6:
                printf("\nThank you for using ROMUS AGENDA!");
                return 0;
            default:
                printf("\nYou have wrong dialed!");
        }
    }

    return 0; 
}

int menu()
{
    int operation = 0;

    printf("\n\n=== ROMUS AGENDA ===\n");
    printf("1. Add Event\n");
    printf("2. List Events\n");
    printf("3. Show Description\n");
    printf("4. Sort Events\n");
    printf("5. Delete Event\n");
    printf("6. Exit\n");
    printf("Please enter a value: ");
    scanf("%d", &operation);
    while (getchar() != '\n');

    return operation;
}

void init_events()
{
    events = malloc(capacity * sizeof(Event));

    file = fopen("agenda.da", "r");
    if (file == NULL)
    {
        file = fopen("agenda.da", "w");
        if (file == NULL)
        {
            perror("\nCouldn't open the file!");
            exit(1);
        }
    }

    char line[500];
    char temp_date[30];
    while (fgets(line, sizeof(line), file))
    {
        if (count == capacity)
        {
            capacity += 3;
            events = realloc(events, capacity * sizeof(Event));
        }

        // Date
        char *part = strtok(line, "|");
        if (part == NULL) continue;
        strcpy(temp_date, part);

        // Title
        part = strtok(NULL, "|");
        if (part == NULL) continue;
        strcpy(events[count].title, part);

        // Description
        part = strtok(NULL, "\0");
        if (part == NULL) continue;
        strcpy(events[count].description, part);

        // Date Subparts
        char *date_part = strtok(temp_date, "/");
        if (date_part == NULL) continue;
        events[count].day = atoi(date_part);

        date_part = strtok(NULL, "/");
        if (date_part == NULL) continue;
        events[count].month = atoi(date_part);

        date_part = strtok(NULL, "\0");
        if (date_part == NULL) continue;
        events[count].year = atoi(date_part);
        count++;
    }

    fclose(file);
}

void add_event()
{
    if (count >= capacity)
    {
        capacity += 3;
        events = realloc(events, capacity * sizeof(Event));
    }

    char title[100];
    char description[200];
    
    printf("\nEnter the title of event: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    printf("Enter the date year: ");
    scanf("%d", &events[count].year);
    while (getchar() != '\n');
    
    printf("Enter the date month: ");
    scanf("%d", &events[count].month);
    while (getchar() != '\n');

    printf("Enter the date day: ");
    scanf("%d", &events[count].day);
    while (getchar() != '\n');

    printf("Enter the description of the event: ");
    fgets(description, sizeof(description), stdin);
    description[strcspn(description, "\n")] = 0;

    strcpy(events[count].title, title);
    strcpy(events[count].description, description);

    count++;

    return;
}

void list_events(Event event_array[])
{
    printf("\n---Events List---\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d- %s - %d/%d/%d\n", i+1, event_array[i].title, event_array[i].day, event_array[i].month, event_array[i].year);
    }

    return;
}

void delete_event()
{
    int index; 

    list_events(events);
    printf("Enter the index of the event you would like to delete: ");
    scanf("%d", &index);
    while (getchar() != '\n');

    for (int i = --index; i < count-1; i++)
    {
        events[i] = events[i+1]; 
    }

    count--;
}

void update_file()
{
    file = fopen("agenda.da", "w");

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d/%d/%d|%s|%s\n", events[i].day, events[i].month, events[i].year, events[i].title, events[i].description);
    }

    fflush(file);
}

void show_description()
{
    int index;

    list_events(events);
    printf("Enter the index of the event you would like to see: ");
    scanf("%d", &index);
    while (getchar() != '\n');

    index--;
    printf("\n%s - %d/%d/%d\n", events[index].title, events[index].day, events[index].month, events[index].year);
    printf("%s", events[index].description);
}

Event* sort_events(const Event event_array[])
{
    Event* sorted = malloc(count * sizeof(Event));
    if (!sorted) return NULL; 

    memcpy(sorted, event_array, count * sizeof(Event));

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            int cmp = 0;
            if (sorted[j].year > sorted[j+1].year) cmp = 1;
            else if (sorted[j].year == sorted[j+1].year && sorted[j].month > sorted[j+1].month) cmp = 1;
            else if (sorted[j].year == sorted[j+1].year && sorted[j].month == sorted[j+1].month && sorted[j].day > sorted[j+1].day) cmp = 1;

            if (cmp)
            {
                Event temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }

    return sorted;
}



// TODO:
// Belirli bir gün seçip onun description okunacak 1
// Add komutu ile kapasite aşılacak 1 
// Delete fonksiyonu denenecek 1
// Sıralama eklenecek  1
// Aynı günkü etkinlikleri grupla
// JSON formatında sakla
// Sadece belli tarih aralığını göster
// Tarih girişinde hatalı girişleri engelle is_valid_date()
// Search event by title
// Update event
// Is tomorrow
// Kategoriye göre gruplandır (doğumgünü, iş, özel)