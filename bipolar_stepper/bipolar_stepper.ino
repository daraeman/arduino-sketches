/*
	Bipolar Stepper motor control
	Full step sequence only
*/
int in1 = 2; // coil 1a
int in2 = 3; // coil 1b
int in3 = 4; // coil 2a
int in4 = 5; // coil 2b
int wait = 500; // time to wait between steps
int pulse_delay = 10; // time to wait before de-energizing coils
int current_sequence = 0;
int sequence_count = 4; // the number of steps in the "sequence" array
int sequence[4][4] = {
	{1, 0, 1, 0},
	{0, 1, 0, 1},
	{0, 1, 1, 0},
	{1, 0, 0, 1}
};

bool stepper( bool coil_1_a, bool coil_1_b, bool coil_2_a, bool coil_2_b, bool lock ) {
	digitalWrite( in1, coil_1_a ? HIGH : LOW );
	digitalWrite( in2, coil_1_b ? HIGH : LOW );
	digitalWrite( in3, coil_2_a ? HIGH : LOW );
	digitalWrite( in4, coil_2_b ? HIGH : LOW );

	// if lock is true, this will keep the coils energized
	// keeping the motor in place, steppers can get quite
	// hot if left like this
	if ( ! lock ) {
		delay( pulse_delay );
		digitalWrite( in1, LOW );
		digitalWrite( in2, LOW );
		digitalWrite( in3, LOW );
		digitalWrite( in4, LOW );
	}
}

bool forward( bool lock ) {
	current_sequence = ( (current_sequence + 1) >= sequence_count ) ? 0 : (current_sequence + 1);
	int *seq = sequence[ current_sequence ];
	stepper( seq[0], seq[1], seq[2], seq[3], lock );
}

bool reverse( bool lock ) {
	current_sequence = ( (current_sequence - 1) < 0 ) ? (sequence_count - 1) : (current_sequence - 1);
	int *seq = sequence[ current_sequence ];
	stepper( seq[0], seq[1], seq[2], seq[3], lock );
}

void setup() {
	pinMode( in1, OUTPUT );
	pinMode( in2, OUTPUT );
	pinMode( in3, OUTPUT );
	pinMode( in4, OUTPUT );
}

void loop() {

	forward( 0 );
	delay( wait );

	forward( 0 );
	delay( wait );

	forward( 0 );
	delay( wait );

	forward( 0 );
	delay( wait );


	reverse( 0 );
	delay( wait );

	reverse( 0 );
	delay( wait );

	reverse( 0 );
	delay( wait );

	reverse( 0 );
	delay( wait );
}
