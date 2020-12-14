// MACROS:

#define LED_ON() PORTB |= 0b00100000
#define LED_OFF() PORTB &= ~0b00100000
#define LED_TOGGLE() PINB |= 0b00100000
#define SW1 (PINB & 0b10000000)
#define SW_PRESSED 0
#define DB_TIME 50

#define true 1
#define false 0
#define FALSE false
#define TRUE true

#define TIMER_DISABLE 0xFFFF

/**
 * Prototypes
 */
void SysInit(void);
void TC1_Init(void);
void CheckSWs(void);

/**
 * Global Variables
 */
uint8_t SW1Pressed_F;
uint8_t SW1ActionTaken_F;

/**
 * Timers
 */
uint16_t msecTimer;
uint16_t TestTimer;
uint16_t SecsCounter;
uint16_t SW1dbTimer;