/**************************************************************
* CCA IxD 300-01/02
* State Machine Walkthrough
* 
**************************************************************/

int buttonPin = 6;
int buttonState = 0;
int lastButtonState = 0;

int inputType = 0;
bool inputAction_FLAG = false;

long firstPressTime = 0;

bool powerState = 0;
int colorState = 0;




void setup() {
	pinMode(buttonPin, INPUT);

	// Set pin modes of LEDs here too (NOT SHOWN)
}




void loop() {

	/**************************************************************
	 * Structure 1
	 * This section READS SENSORS (BUTTON)
	 * This section OUTPUTS INPUTS (0 or 1)
	 **************************************************************/

	// Store previous button state before reading new one
	lastButtonState = buttonState;

	// Read current button state
	buttonState = digitalRead(buttonPin);

	bool buttonChanged = (buttonState == lastButtonState);

	if ( buttonChanged ) {
		if ( buttonState ){
		    firstPressTime = millis();
		}
		else {
			// Set Action FLAG to true to trigger action later in loop()
			inputAction_FLAG = true;

			// Store the time elapsed since button was first pressed
			long timeSincePress = millis() - firstPressTime;

			// Check to see if time since the button was pressed is < 5 seconds
			if ( timeSincePress < 5000 ) {
				inputType = 0;
			}
			else {
				inputType = 1;
			}
		}
	}


	 /**************************************************************
	 * Structure 2
	 * This section TAKES INPUTS AND CURRENT STATE
	 * This section OUTPUTS TO THE ACTUATORS (LEDS)
	 **************************************************************/

	if ( powerState == 0 ) {
		ledOff();
	}
	else {
		setColor(colorState);
		ledOn();
	}


	 /**************************************************************
	 * Structure 3
	 * This section TAKES INPUTS and CURRENT STATE
	 * This section DETERMINES NEXT STATE
	 **************************************************************/

	 if ( inputAction_FLAG ) {
		if ( (inputType == 0) && (powerState == 1) ) {
			cycleColor();
		}
		if ( inputType == 1 ) {
			cyclePower();
		}
	}
	inputAction_FLAG = false;

}





/**************************************************************
* FUNCTIONS
**************************************************************/

void ledOn() {
	// Code to turn on LED here (NOT SHOWN)
}

void ledOff() {
	// Code to turn off LED here (NOT SHOWN)
}

void setColor(int _colorState) {
	// Code to set the LED to the color input to the function (NOT SHOWN)
}

void cycleColor() {
	colorState++;
	colorState = colorState % 3; // Look up modulo.  This does nothing when the value is 0, 1, 2.  But when it reaches 3, it resets it to 0. Note we only have 3 colors.
}

void cyclePower() {
	powerState = !powerState; // This switches powerState between 0 and 1.
}