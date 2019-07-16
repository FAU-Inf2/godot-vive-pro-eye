extends ARVROrigin

func _ready():
	var interface = ARVRServer.find_interface("OpenVR")
	if interface and interface.initialize():
		get_viewport().arvr = true
		get_viewport().hdr = false
	else:
		print("failed to init openvr")