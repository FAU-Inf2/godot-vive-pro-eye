extends Spatial

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

func vec3(x):
	return Vector3(x,x,x)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	var success = $EyeTracker.update_eye_data()
	if success:
		$LeftMarker.translation = $EyeTracker.get_gaze_direction(-1) + $EyeTracker.get_eyeball_position(-1)
		$LeftMarker.scale = vec3($EyeTracker.get_eye_openness(-1))
		$RightMarker.translation = $EyeTracker.get_gaze_direction(1) + $EyeTracker.get_eyeball_position(1)
		$RightMarker.scale = vec3($EyeTracker.get_eye_openness(1))
		$CombinedMarker.translation = $EyeTracker.get_gaze_direction(0)
	else:
		print("error updating eye data!")
