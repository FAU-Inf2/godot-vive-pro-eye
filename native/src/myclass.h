#pragma once

#include <Godot.hpp>
#include <Spatial.hpp>
#include <Material.hpp>
#include <MeshInstance.hpp>

#include "SRanipal.h"
#include "SRanipal_Eye.h"

namespace godot {

class MyClass : public godot::Node {
	GODOT_CLASS(MyClass, godot::Node)

private:
	bool init_success = false;
	bool data_valid = false;

	ViveSR::anipal::Eye::EyeData eye_data;

	const ViveSR::anipal::Eye::SingleEyeData* get_eye(int eye);

public:
	static void _register_methods();
	
	/** Must be called each frame before get_eyeball_position() or
	    get_gaze_direction() is called. Returns true on success or
		false on error. In the error case, the get_* methods return
		garbage data.
	*/
	bool update_eye_data();

	/** returns the eye gaze origin in meters.
	    The Vector3 returned follows the godot convention, i.e.
		right/up/viewing direction = +x / +y / -z.
		Note that this is different from the SRanipal convention.
	*/
	Vector3 get_eyeball_position(int eye);

	/** returns the normalized eye gaze direction.
	    The Vector3 returned follows the godot convention, i.e.
		right/up/viewing direction = +x / +y / -z.
		Note that this is different from the SRanipal convention.
	*/
	Vector3 get_gaze_direction(int eye);

	/** returns whether a user is present */
	bool is_user_present();

	/** returns the timestamp of the current eye data */
	double get_timestamp();

	/** returns the estimated gaze distance based on the convergence
	    of the two eyes. returns -1 if unknown */
	double get_gaze_distance();

	/** returns the pupil diameter in mm */
	double get_pupil_size(int eye);

	/** returns whether the eye is open (1) or closed(0) or in between */
	double get_eye_openness(int eye);

	MyClass();
	~MyClass();
	void _init();
};

}
