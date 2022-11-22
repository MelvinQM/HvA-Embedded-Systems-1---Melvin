## Blinkie opdracht 1
## Gemaakt door: Melvin Moes, 500905603, 17-11-2022

```
//Importing gpio drivers
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

//Defining the Led Pin 
#define LED_PIN 21

//Main code
void app_main() {
    //Setting power direction
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    //Turning Led on
    gpio_set_level(LED_PIN, HIGH);
    //Adding a delay between turning the Led on and off
    vTaskDelay(1000 / portTICK_PERIOD_MS); // 1000 milliseconde = 1 seconde
    //Turning Led off
    gpio_set_level(LED_PIN, LOW);
}
```
- Wat is het verschil tussen software en firmware?
>Firmware is software dat ingebakken staat in hardware.
- Wat is een microcontroller?
>Een microcontroller is eigenlijk een soort mini computer.
- In wat voor apparaten vind je allemaal microcontrollers?
>In bijna alles van huishoudelijke apparaten tot auto's.
- Wat voor verschillen vind je tussen jouw PC en een microcontroller?
>Een micro controller is een stuk simpeler in elkaar gezet omdat het vaak niet zo veel functies nodig heeft.
- Wat verstaan wij onder Internet of Things, wat zie je hiervan hedendaags?
>Het verbinden van steeds meer apparaten aan het internet.
- Hoe zit het met de 'sjoemelsoftware' wat in 2015 ontdekt werd bij onder andere Volkswagen?
>Software die gebruikt wordt om testresultaten te beïnvloeden van een elektronisch apparaat of machine. Dit is vaak in het voordeel van de makers van deze software. Dit werd door volkwswagen gebruikt om de testen die auto's moesten volgen nepresultaten kregen. Zodat ze weg konde komen met in principe fraude.
- Waarvoor dient het besturingssysteem? Wat voor besturingssysteem draai jij op je PC? En op je ESP32? Op je Odroid?
>Op mijn computer draai ik windows 11. De esp32 draait op linux. Deze systemen zijn er om het apparaat te kunnen laten werken.
- Wat is nou een Embedded Systeem? Wat is kenmerkend voor een Embedded Systeem?
>Een embedded system is een system die in het hardware verwerkt zijn. Ze zijn bijna onzichtbaar. Mensen zijn er vaak niet bewust van dat er uberhaupt een system in zit.
- Waarin zitten allemaal Embedded Systemen? Wat hebben deze als doel?
>Het raam van je auto, dit systeem regelt dan bijvoorbeeld de op en neer beweging van het raam.
- Wat zijn computers, van klein tot groot, de heletijd aan het doen?
>Ze kunnen wachten op iets zoals een voorwaarde. Het kan waardes meten zoals temperatuur of geluid.
- Wat zijn digitale gegevens? Welke voordelen hebben deze?
>Digitale gegevens zijn alle waades die je kan meten met systemen.
- Waarom is een processor zo belangrijk in een computersysteem?
>Een processor is ervoor om de instructies te kunnen lezen die het apparaat/systeem uit moet voeren
- Wat voor processor heeft jouw pc, telefoon, ESP32, Odroid, ...?
>Mijn laptop heeft een intel i7 cpu, Mijn esp32 heeft een Xtensa dual-core, Mijn mobiel is een iPhone 10 deze heeft een Apple A11 chipset.
- Waarom hebben we high-level programmeertalen? Wat is 'high', wat is 'low'?
>High programeertalen zijn talen die eenvoudige instructies kunnen versimpelen. Lagere programeertalen moet je dus veel meer code schrijven om hetzelfde resultaat te krijgen.
- Waarom schrijf je software voor een Embedded Systeem vaak niet op het apparaat zelf?
>Omdat werken op een embedded system is vaak veel ingewikkelder is door geen 
- Wat zijn de (technische) specificaties van jouw Embedded Boardje?
>The ESP32-S3-DevKitC-1 is an entry-level development board equipped with ESP32-S3-WROOM-1, ESP32-S3-WROOM-1U, or ESP32-S3-WROOM-2, a general-purpose Wi-Fi + Bluetooth® LE MCU module that integrates complete Wi-Fi and Bluetooth LE functions.
- Wat is het verschil tussen interpreteren en compileren?
>Interpreteren is de hele code omzetten regel per regel naar te lezen instructies voor het systeem. Compileren doet in principe hetzelfde alleen doet deze de hele code en slaat dit vervolgens op zodat het systeem het volgende keer meteen kan gebruiken. 
- Beschrijf globaal de werking van een computersysteem.
>Een computer systeem bevat een processor die instructies krijgt van de firmware/software die het systeem draaiend heeft. Deze instructies worden verwerkt naar acties zoals de beweging van een motor of het geven van een signaal naar bijvoorbeeld jouw beeldscherm die dan aangaat.


