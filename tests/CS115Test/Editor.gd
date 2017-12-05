extends Node2D

var interpreter
var floor_map;
var init_ent;
onready var my_ent = preload("res://Ent.tscn")

func _ready():
	interpreter = Interpreter.new()
	
	floor_map = Floor_Map.new()
	floor_map.init(1, 1)
	
	var room = Room_Map.new()
	room.init(floor_map, 0, 0, 2, 2)
	
	floor_map.set_room(room, 0, 0)
	
	var tile = room.get_tile(0, 0)
	
	var entity = Entity.new()
	var my_ent_node = my_ent.instance()
	add_child(my_ent_node)
	entity.init(my_ent_node.get_path(), tile)
	tile.set_entity(entity)
	
	var success = entity.move_tile_relative(1, 1)
	print(success)
	print(room.get_tile(1, 1).get_entity().get_node_path())
	init_ent = entity


func _on_Init_button_down():
	var editor = get_node("TextEdit")
	var code = editor.get_text()
	interpreter.init(code, init_ent)


func _on_Run_button_down():
	interpreter.run()
	var out = interpreter.get_test_output()
	var label = get_node("Output")
	label.set_text(String(out))


func _on_Finalize_button_down():
	interpreter.finalize()
