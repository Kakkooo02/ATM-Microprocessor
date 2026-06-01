# ATM Microprocessor

ATM Microprocessor is an embedded C project that simulates a basic ATM transaction system using UART communication, GPIO pins, keypad input, PIN verification, timeout handling, and withdrawal validation.

## Overview

The system starts when a hardware switch is pressed. It asks the user to enter a 5-digit PIN using a keypad, checks whether the PIN is correct, and allows up to three attempts. If the PIN is correct, the user is asked to enter a withdrawal amount through UART. The system then checks for timeout, validates the amount, and displays whether the transaction was successful or rejected due to insufficient balance.

This project was developed to practice microcontroller programming, hardware input handling, UART serial communication, and basic embedded system logic.

## Features

* UART0 initialization for serial communication
* GPIO configuration for switch and keypad input
* 5-digit PIN verification
* Maximum of 3 PIN attempts
* Keypad scanning using GPIO rows and columns
* Withdrawal amount input through UART
* Timeout handling if the user does not respond
* Balance validation
* Transaction success and failure messages

## Tech Stack

| Area                   | Technology                    |
| ---------------------- | ----------------------------- |
| Language               | C                             |
| Communication          | UART                          |
| Input                  | GPIO, keypad, hardware switch |
| Microcontroller header | MKL25Z4                       |


## System Flow

```text
Start
  ↓
Initialize UART and GPIO
  ↓
Wait for switch press
  ↓
Ask user to enter PIN
  ↓
Check PIN
  ↓
If PIN is wrong, allow up to 3 attempts
  ↓
If PIN is correct, ask for withdrawal amount
  ↓
Check for timeout
  ↓
Validate withdrawal amount
  ↓
Display transaction result
```

## Transaction Logic

* The system waits for a switch input before starting.
* The user enters a 5-digit PIN using the keypad.
* The default PIN used in the code is:

```text
12345
```

* The user has a maximum of 3 attempts.
* If all attempts fail, the transaction is aborted.
* If the PIN is correct, the user enters a withdrawal amount.
* If the amount is greater than the allowed balance, the system displays an insufficient balance message.
* Otherwise, the transaction is completed successfully.

## File Structure

```text
ATM-Microprocessor/
├── atm_microprocessor.c
└── README.md
```

## Important Functions

| Function        | Purpose                                           |
| --------------- | ------------------------------------------------- |
| `UART0_init()`  | Initializes UART communication                    |
| `keypad()`      | Reads keypad input using GPIO                     |
| `delay()`       | Creates a basic delay loop                        |
| `short_delay()` | Creates a shorter delay used for timeout checking |
| `timeout()`     | Displays a timeout message                        |

## How to Run

1. Open the project in an embedded C development environment.
2. Connect the supported microcontroller board.
3. Build and flash the program to the board.
4. Open a UART serial terminal.
5. Press the hardware switch to start the ATM process.
6. Enter the PIN using the keypad.
7. Enter the withdrawal amount through UART.
8. View the transaction result in the serial terminal.

## What I Learned

Through this project, I practiced:

* Configuring GPIO pins for input and output
* Using UART for serial communication
* Reading keypad input in an embedded system
* Writing conditional logic for authentication
* Handling timeout behavior
* Designing a simple transaction workflow
* Working with microcontroller registers directly

## Future Improvements

* Hide PIN digits instead of displaying them through UART
* Store PIN and balance more securely
* Add an LCD display for better user interaction

## Author

Created by Kakkooo02
