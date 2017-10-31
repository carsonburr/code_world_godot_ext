extends Node2D

var text_node
var run_button_node
var result_node
var interpreter

var firstrun

func _ready():
	interpreter = Code_World.new()
	firstrun = true
	
	text_node = get_node("TextEdit")
	run_button_node = get_node("Button")
	result_node = get_node("Label")
	
	run_button_node.connect("pressed",self,"_on_button_pressed")

func _on_button_pressed():
	firstrun = false
	
	var code = text_node.get_text()
	
	var init_success = interpreter.init(code)
	if (!init_success):
		result_node.set_text("init failed")
		return
	
	var run_success = interpreter.run()
	if (!run_success):
		result_node.set_text("run failed")
		interpreter.finalize()
		return
	
	var output = interpreter.get_output()
	result_node.set_text(String(output))
	
	interpreter.finalize()