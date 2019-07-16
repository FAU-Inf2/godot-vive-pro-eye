#pragma once

#include <Godot.hpp>
#include <Spatial.hpp>
#include <Material.hpp>
#include <MeshInstance.hpp>

#include "SRanipal.h"
#include "SRanipal_Eye.h"

#include <boost/lockfree/spsc_queue.hpp>
#include <optional>
#include <thread>

namespace godot {

class MyClass : public godot::Node {
	GODOT_CLASS(MyClass, godot::Node)

private:
	bool data_valid = false;
	ViveSR::anipal::Eye::EyeData eye_data;
	/** gives the left, combined or right eye data for eye = -1/0/1 */
	const ViveSR::anipal::Eye::SingleEyeData* get_eye(int eye);

	boost::lockfree::spsc_queue<ViveSR::anipal::Eye::EyeData, boost::lockfree::capacity<2>> queue;
	// queue MUST be listed before poll_thread. It is important that poll_thread
	// gets destructed PRIOR to queue!
	std::thread poll_thread; // required for getting the full 120Hz from the HMD

	void poll();

public:
	static void _register_methods();
	
	/** Updates the internal state to the latest eye data available.
		Returns true if the eye data was updated or false if no new data
		was available.

		One of update_eye_data() or next_eye_data() must be called each frame
		before get_eyeball_position() or get_gaze_direction() is called. Returns
		true on success or false on error. In the error case, the get_* methods
		return garbage data.
	*/
	bool update_eye_data();

	/** Updates the internal state to the next eye data in the ringbuffer, if
		available, and returns true in that case. Does nothing and returns false
		otherwise.

		One of update_eye_data() or next_eye_data() must be called each frame
		before get_eyeball_position() or get_gaze_direction() is called. Returns
		true on success or false on error. In the error case, the get_* methods
		return garbage data.
	*/
	bool next_eye_data();

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
