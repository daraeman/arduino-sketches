/*
	Bipolar Stepper motor control
*/
int in1 = 2; // coil 1a
int in2 = 3; // coil 1b
int in3 = 4; // coil 2a
int in4 = 5; // coil 2b
int wait = 300; // time to wait between steps
// time to wait before de-energizing the
// coils, letting the rotor move positions.
// some motors need more pulse delay than others
int pulse_delay = 10;
int current_sequence = 0;
int sequence_count = 8; // the number of steps in the "sequence" array

/*
	wave drive (single phase)
	for some reason on the cheap stepper motor I tested,
	each step is actually two steps.
	Also coil one is forwards,
	coil two is backwards
*/
/*
int sequence[4][4] = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
//	{0, 0, 1, 0},
//	{0, 0, 0, 1}
};
*/

/*
	two phase
	full steps
*/
/*
int sequence[4][4] = {
	{1, 0, 0, 1},
	{1, 0, 1, 0},
	{0, 1, 1, 0},
	{0, 1, 0, 1}
};

/*
	half step
*/

int sequence[8][4] = {
	{1, 0, 0, 1},
	{0, 0, 0, 1},
	{0, 1, 0, 1},
	{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 1, 0},
	{1, 0, 1, 0},
	{1, 0, 0, 0}
};


bool stepper( bool coil_1_a, bool coil_1_b, bool coil_2_a, bool coil_2_b, bool lock ) {
	digitalWrite( in1, coil_1_a ? HIGH : LOW );
	digitalWrite( in2, coil_1_b ? HIGH : LOW );
	digitalWrite( in3, coil_2_a ? HIGH : LOW );
	digitalWrite( in4, coil_2_b ? HIGH : LOW );

	// if lock is true, this will keep the coils energized
	// keeping the motor in place, best to turn this off if
	// it is not necessary since steppers get really hot if
	// left on
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
	current_sequence = ( current_sequence == 0 ) ? (sequence_count - 1) : (current_sequence - 1);
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

	for ( int i = 0; i < 24; i++ ) {
		forward( 0 );
		delay( wait );
	}

	for ( int i = 0; i < 24; i++ ) {
		reverse( 0 );
		delay( wait );
	}

}