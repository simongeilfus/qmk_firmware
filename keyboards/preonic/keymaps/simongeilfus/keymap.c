/*
* Download or Clone QMK Firmware: <https://github.com/qmk/qmk_firmware/>
* Extract QMK Firmware to a location on your hard drive
* Run `util/qmk_install.sh`
* You are now ready to compile or use your keymap with the source
* Build & Flash firmware using `make preonic/rev3:simongeilfus:flash
*/

#include QMK_KEYBOARD_H
#include "process_auto_shift.h"
#include "tapdance.h"
#include "utils.h"
#ifdef AUDIO_ENABLE
#include "audio.h"
#endif

enum preonic_keycodes {
	M_PTR = SAFE_RANGE,
	VS_HEADER,
	VS_PEEK_HEADER,
	LS_BASE,
	LS_GAME
};

enum tapdance_keycodes {
	TD_ESC = 0,
	TD_POINTER,
	TD_LFT,
	TD_DWN,
	TD_UP,
	TD_RGT,
	TD_STEP_INTO
};

enum layer_names {
	L_BASE = 0,
	L_GAME,
	L_LOWER,
	L_RAISE,
	L_ADJUST,
	L_VISUALSTUDIO
};

#define L_B 		L_BASE
#define L_L 		L_LOWER
#define L_R 		L_RAISE
#define L_A			L_ADJUST
#define L_VS 		L_VISUALSTUDIO

#define SHESC 		SFT_T(KC_ESC)
#define POINTER 	TD(TD_POINTER)
#define STEPINTO	TD(TD_STEP_INTO)

float sound_base[][2] = SONG(DVORAK_SOUND);
float sound_game[][2] = SONG(WORKMAN_SOUND);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* BASE
	* ,-----------------------------------------------------------------------------------.
	* | ` ~  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* |  ->  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* | ShEsc|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  /   |ShEntr|
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* | Ctrl |      | WIN  | Alt  |Lower |    Space    | Raise| Left | Down |  Up  | Right|
	* `-----------------------------------------------------------------------------------'
	*/
	[L_BASE] = LAYOUT_preonic_1x2uC(
		KC_GRAVE,	KC_1,		KC_2,		KC_3,		KC_4,		KC_5,		KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,	\
		POINTER,	KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_BSPC,	\
		KC_TAB,		KC_A,		KC_S,		KC_D,		KC_F,		KC_G,		KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,	KC_QUOT,	\
		SHESC,		KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,	KC_SFTENT,	\
		KC_LCTL,	XXXXXXX,	KC_LGUI,	KC_LALT,	MO(L_L),		KC_SPC,				MO(L_R),	KC_LEFT,	KC_DOWN,	KC_UP,      KC_RIGHT	\
		),


	/* LOWER Programming / Symbols and Navigation
	* ,-----------------------------------------------------------------------------------.
	* |      |      |      |      |      |      |      |   &  |   *  |   (  |   )  |  =   |
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* |      |      | PGUP | PGDN |      |      |      |   |  |   +  |   {  |   }  |  Del |
	* |------+------+------+------+------+-------------+------+------+------+------+------|
	* |      | Home | NextW| PrevW|  End |      |      |      |   =  |   [  |   ]  |      |
	* |------+------+------+------+------+------|------+------+------+------+------+------|
	* |      |      |      |      |      |      |      |      |      |  ->  |      |      |
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* |      |      |      |      |      |             |Adjust|   \  |      |      |      |
	* `-----------------------------------------------------------------------------------'
	*/
	[L_LOWER] = LAYOUT_preonic_1x2uC(
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	KC_AMPR,	KC_ASTR,	KC_LPRN,	KC_RPRN,	KC_EQL,		\
		XXXXXXX,	XXXXXXX,	KC_PGUP,	KC_PGDN,	XXXXXXX,	XXXXXXX,	XXXXXXX,	KC_PIPE,	KC_PPLS,	KC_LCBR,	KC_RCBR,	KC_DEL,		\
		XXXXXXX,	KC_HOME,	C(KC_LEFT),	C(KC_RIGHT),KC_END,		XXXXXXX,	XXXXXXX,	XXXXXXX,	KC_EQL,	    KC_LBRC,	KC_RBRC,	XXXXXXX,	\
		_______,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	M_PTR,		KC_BSLS,	_______,	\
		_______,	XXXXXXX,	XXXXXXX,	_______,	_______,		XXXXXXX,			MO(L_A),	KC_HOME,	KC_PGDN,	KC_PGUP,	KC_END		\
		),


	/* RAISE F-Keys and Mouse Keys
	* ,-----------------------------------------------------------------------------------.
 	* |      |      |      |      |      |      |      |      |      |      |      |      |
 	* |------+------+------+------+------+------+------+------+------+------+------+------|
 	* |      |      |WheelU|WheelD|      |      |      |  F1  |  F2  |  F3  |  F4  |      |
 	* |------+------+------+------+------+-------------+------+------+------+------+------|
 	* |      | Left | Down |  Up  | Right|      |      |  F5  |  F6  |  F7  |  F8  |      |
 	* |------+------+------+------+------+------|------+------+------+------+------+------|
 	* |      |      |      |       |     |      |      |  F9  |  F10 |  F11 |  F12 |      |
 	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* |      |      |      |      |Adjust|             |      |      | Vol- | Vol+ |      |
	* `-----------------------------------------------------------------------------------'
	*/
	[L_RAISE] = LAYOUT_preonic_1x2uC(
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	KC_UNDS,	\
		XXXXXXX,	XXXXXXX,	KC_WH_U,	KC_WH_D,	XXXXXXX,	XXXXXXX,	XXXXXXX,	KC_F1,		KC_F2,		KC_F3,		KC_F4,	    XXXXXXX,    \
		XXXXXXX,	KC_LEFT,	KC_DOWN,	KC_UP,      KC_RIGHT,	XXXXXXX,	XXXXXXX,	KC_F5,		KC_F6,	    KC_F7,		KC_F8,	    XXXXXXX,	\
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	KC_F9,		KC_F10,		KC_F11,		KC_F12,	    XXXXXXX,	\
		_______,	XXXXXXX,	XXXXXXX,	_______,	MO(L_A),		XXXXXXX,			_______,	XXXXXXX,	XXXXXXX,	KC_VOLD,	XXXXXXX		\
		),


	/* ADJUST
	* ,-----------------------------------------------------------------------------------.
 	* | Reset| BASE | GAME |      |      |      |      |      |      |      |      |EEProm|
 	* |------+------+------+------+------+------+------+------+------+------+------+------|
 	* |      |      |      |      |      |      |      |      |      |      |      |      |
 	* |------+------+------+------+------+-------------+------+------+------+------+------|
 	* |      |      |      |      |      |      |      |      |      | MU_ON|MU_OFF|MU_MOD|
 	* |------+------+------+------+------+------|------+------+------+------+------+------|
 	* |      |      |      |      |      |      |      |      |      | ASON | ASOFF|      |
 	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* |      |      |      |      |      |             |      |      | ASDN | ASUP | ASRP |
	* `-----------------------------------------------------------------------------------'
	*/
	[L_ADJUST] = LAYOUT_preonic_1x2uC(
		RESET,		LS_BASE,	LS_GAME,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	EEP_RST,	\
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	\
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	MU_ON,		MU_OFF,		MU_MOD,		\
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	KC_ASON,	KC_ASOFF,	XXXXXXX,	\
		XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	_______,		XXXXXXX,			_______,	XXXXXXX,	KC_ASDN,	KC_ASUP,	KC_ASRP		\
		),


	/* VISUALSTUDIO
	* ,-----------------------------------------------------------------------------------.
	* |      | BACK |FORWRD|      |      |      |      |      |      |      |      |      |
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* | ____ | AF12 | F12  |      |      |      |      |      |      |      |      | BREAK|
	* |------+------+------+------+------+-------------+------+------+------+------+------|
	* |     |PHEADER|HEADER|      |      |      |      | Build| Debug|LivePP|      |      |
	* |------+------+------+------+------+------|------+------+------+------+------+------|
	* | STOP |      |      |      |      |      |      |      |      |      |    |CONTINUE|
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* |      |      |      |      |      |             |      |RESTRT| SINTO| SOUT | SOVER|
	* `-----------------------------------------------------------------------------------'
	*/
	[L_VISUALSTUDIO] = LAYOUT_preonic_1x2uC(
		XXXXXXX,    KC_WBAK,	KC_WFWD,  	XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,		XXXXXXX,  	XXXXXXX,  XXXXXXX, \
		_______,	A(KC_F12),	KC_F12,  	XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,		XXXXXXX,  	XXXXXXX,  C(A(KC_PAUSE)), \
		XXXXXXX,VS_PEEK_HEADER,	VS_HEADER,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  C(S(KC_B)),  KC_F5,		C(A(KC_F11)), XXXXXXX,  XXXXXXX, \
		S(KC_F5), 	XXXXXXX,  	XXXXXXX,  	XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,		XXXXXXX,  	XXXXXXX,  KC_F5, \
		XXXXXXX,  	XXXXXXX,  	XXXXXXX,  	XXXXXXX,  XXXXXXX,       XXXXXXX,       XXXXXXX,  C(S(KC_F5)),	STEPINTO,  S(KC_F11), KC_F10   \
	),

	/* GAME
	* ,-----------------------------------------------------------------------------------.
	* | ` ~  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* |  Esc |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  /   |Enter |
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* | Ctrl |Macro1|      | Alt  |Lower |    Space    | Raise| Left | Down |  Up  | Right|
	* `-----------------------------------------------------------------------------------'
	*/
	[L_GAME] = LAYOUT_preonic_1x2uC(
		KC_GRAVE,	KC_1,		KC_2,		KC_3,		KC_4,		KC_5,		KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,	\
		KC_ESC,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_BSPC,	\
		KC_TAB,		KC_A,		KC_S,		KC_D,		KC_F,		KC_G,		KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,	KC_QUOT,	\
		KC_LSFT,	KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,	KC_ENTER,	\
		KC_LCTL,	XXXXXXX,	XXXXXXX,	KC_LALT,	MO(L_L),		KC_SPC,				MO(L_R),	KC_LEFT,	KC_DOWN,	KC_UP,      KC_RIGHT	\
		)
};

// Startup
//______________________________________________________________________________

void keyboard_post_init_user(void)
{
#ifdef AUTO_SHIFT_ENABLE
	// disable auto-shift
	autoshift_disable();
#endif
}

// Process Record
//______________________________________________________________________________

bool process_record_user( uint16_t keycode, keyrecord_t *record )
{
	switch (keycode) {
	case M_PTR:
		if( record->event.pressed ) {
			SEND_STRING( "->" );
		}
		// Skip all further processing of this key
		return false;

	case VS_HEADER:
		if( record->event.pressed ) {
			register_code( KC_LCTL );
			tap_code( KC_K );
			tap_code( KC_O );
			unregister_code( KC_LCTL );
		}
		return false;

	case VS_PEEK_HEADER:
		if( record->event.pressed ) {
			register_code( KC_LCTL );
			tap_code( KC_K );
			tap_code( KC_J );
			unregister_code( KC_LCTL );
		}
		return false;

	case LS_BASE:
		if( record->event.pressed ) {
			default_layer_set( 1UL<<L_BASE );
#ifdef AUDIO_ENABLE
			PLAY_SONG( sound_base );
#endif
		}
		return false;

	case LS_GAME:
		if( record->event.pressed ) {
			default_layer_set( 1UL<<L_GAME );
#ifdef AUDIO_ENABLE
			PLAY_SONG( sound_game );
#endif
		}
		return false;

	// case KC_ENTER:
	// 	// Play a tone when enter is pressed
	// 	if (record->event.pressed) {
	// 		PLAY_NOTE_ARRAY(tone_qwerty);
	// 	}
	// 	return true; // Let QMK send the enter press/release events

	default:
		// Process all other keycodes normally
		return true;
	}
}

// Tap Dance
//______________________________________________________________________________

// Pointer Tap Dance

static TapDance pointer_tap_state = {
  .is_press_action = true,
  .state = 0
};

void pointer_tap_finished (qk_tap_dance_state_t *state, void *user_data)
{
	pointer_tap_state.state = getDanceState(state);
  	switch (pointer_tap_state.state) {
     	case SINGLE_TAP: register_code(KC_F5); break;
     	case DOUBLE_TAP: register_code(KC_LCTL); register_code(KC_LSFT); register_code(KC_B); break;
		case SINGLE_HOLD: layer_on(L_VISUALSTUDIO); break;
  	}
}

void pointer_tap_reset (qk_tap_dance_state_t *state, void *user_data)
{
  	switch (pointer_tap_state.state) {
     	case SINGLE_TAP: unregister_code(KC_F5); break;
     	case DOUBLE_TAP: unregister_code(KC_LCTL); unregister_code(KC_LSFT); unregister_code(KC_B); break;
		case SINGLE_HOLD: layer_off( L_VISUALSTUDIO ); break;
  	}
  	pointer_tap_state.state = 0;
}

// Tap Dance impl.

qk_tap_dance_action_t tap_dance_actions[] = {
  //[TD_ESC]     = ACTION_TAP_DANCE_FN_ADVANCED( NULL, esc_tap_finished, esc_tap_reset ),
  [TD_POINTER]	= ACTION_TAP_DANCE_FN_ADVANCED( NULL, pointer_tap_finished, pointer_tap_reset ),
  [TD_LFT]		= ACTION_TAP_DANCE_DOUBLE( KC_LEFT, C(KC_LEFT) ),
  [TD_DWN]		= ACTION_TAP_DANCE_DOUBLE( KC_DOWN, KC_HOME ),
  [TD_UP]		= ACTION_TAP_DANCE_DOUBLE( KC_UP, KC_END ),
  [TD_RGT]		= ACTION_TAP_DANCE_DOUBLE( KC_RIGHT, C(KC_RIGHT) ),
  [TD_STEP_INTO]= ACTION_TAP_DANCE_DOUBLE( KC_F11, S(A(KC_F11)) )
};
