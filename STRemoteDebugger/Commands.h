#ifndef _COMMANDS_H
#define _COMMANDS_H

// commands to send to target
enum
{
	// request cmds
	DEBUGGER_CMD_NONE = 0,
	DEBUGGER_CMD_CONNECT = 1,
	DEBUGGER_CMD_DISCONNECT = 2,
	DEBUGGER_CMD_STEP_OVER = 3,
	DEBUGGER_CMD_STEP_INTO = 4,
	DEBUGGER_CMD_STEP_OUT = 5,
	DEBUGGER_CMD_RUN = 6,
	DEBUGGER_CMD_RUN_TO_CURSOR = 7,
	DEBUGGER_CMD_STOP = 8,
	DEBUGGER_CMD_REQUEST_MEMORY = 9,
	DEBUGGER_CMD_REQUEST_REGISTERS = 10,
	DEBUGGER_CMD_SET_PC = 11,

	// response types
	DEBUGGER_TARGET_RESPONSE_NONE = 128,
	DEBUGGER_TARGET_RESPONSE_CONNECTED = 129,
	DEBUGGER_TARGET_RESPONSE_DISCONNECTED = 130,
	DEBUGGER_TARGET_RESPONSE_MEMORY = 131,
	DEBUGGER_TARGET_RESPONSE_REGISTERS = 132,
	DEBUGGER_TARGET_RESPONSE_STEP_OVER = 133,
	DEBUGGER_TARGET_RESPONSE_STEP_INTO = 134,
	DEBUGGER_TARGET_RESPONSE_STEP_OUT = 135,
	DEBUGGER_TARGET_RESPONSE_RUN = 136,
	DEBUGGER_TARGET_RESPONSE_RUN_TO_CURSOR = 137,
	DEBUGGER_TARGET_RESPONSE_STOP = 138,
	DEBUGGER_TARGET_RESPONSE_SET_PC = 139,

} _DEBUGGER_CMD_TYPE;

#endif // _COMMANDS_H