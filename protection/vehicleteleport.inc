/*

	About: vehicle teleport protection
	Author: ziggi & amagida

*/

#if !defined _protection_included
	#error "Please include protection before vehicleteleport"
#endif

#if defined _protection_vehicletp_included
	#endinput
#endif

#define _protection_vehicletp_included

/*
	OnUnoccupiedVehicleUpdate
*/

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
	new bool:is_enabled = Protection_GetParamInt(PROTECTION_VEHICLETELEPORT, PROTECTION_ENABLED) != 0;

	if (is_enabled) {
		static
			Float:distance,
			Float:max_distance,
			Float:pos_x,
			Float:pos_y,
			Float:pos_z,
			Float:angle;

		GetVehiclePos(vehicleid, pos_x, pos_y, pos_z);
		GetVehicleZAngle(vehicleid, angle);
		distance = VectorSize(pos_x - new_x, pos_y - new_y, pos_z - new_z);
		max_distance = Protection_GetParamFloat(PROTECTION_VEHICLETELEPORT, PROTECTION_MAX_DISTANCE);

		if (distance > max_distance && pos_z > -70.0) {
			// set right pos and angle
			SetVehiclePos(vehicleid, pos_x, pos_y, pos_z);
			SetVehicleZAngle(vehicleid, angle);

			// report
			Protection_GivePlayerWarning(playerid, PROTECTION_VEHICLETELEPORT, "%.2f > %.2f", distance, max_distance);
			return 0;
		}
	}

	#if defined PVeTP_OnUnoccupiedVehicleUpdate
		return PVeTP_OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, new_x, new_y, new_z, vel_x, vel_y, vel_z);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnUnoccupiedVehicleUpdate
	#undef OnUnoccupiedVehicleUpdate
#else
	#define _ALS_OnUnoccupiedVehicleUpdate
#endif

#define OnUnoccupiedVehicleUpdate PVeTP_OnUnoccupiedVehicleUpdate
#if defined PVeTP_OnUnoccupiedVehicleUpdate
	forward PVeTP_OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z);
#endif
