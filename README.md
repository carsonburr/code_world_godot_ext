## Copy of the godot engine with added module for code_world  
link to most recent executable: https://www.dropbox.com/sh/5abcqw3idghleek/AABzjBqElM1cWP3MmvqVndzna?dl=0

## Documentation

### Entity  
Any object in godot (read node) that we want to represent to the interpreter

##### Properties:  
<dl>
	<dt>NodePath node</dt>
		<dd>the path to the godot node the entity represents. For use with get_node(NodePath)</dd>
		<dd>get_node_path(), set_node_path(NodePath node)</dd>
	<dt>Room_Tile tile</dt>
		<dd>the tile that the entity resides in</dd>
		<dd>get_tile(), set_tile(Room_Tile tile)</dd>
</dl>

##### Member functions:  
<dl>
	<dt>void init(NodePath node, Room_Tile tile)</dt>
		<dd>initializes the entity, other functions (including get/set) will not work until init is called</dd>
	<dt>bool is_initialized()</dt>
		<dd>check if entity is initialized</dd>
	<dt>bool move_tile(int x, int y)</dt>
		<dd>move the entity to another tile in the same room. returns success</dd>
	<dt>bool move_tile_relative(int x, int y)</dt>
		<dd>move the entity to another tile relative to current tile. returns success</dd>
	<dt>bool move_tile_room(Room_Map room, int x, int y)(int x, int y)</dt>
		<dd>move the entity to a tile in a new room. returns success</dd>
</dl>

### Room_Tile

##### Properties:  
<dl>
	<dt>Room_Map room</dt>
		<dd>the room that the tile resides in</dd>
		<dd>get_room()</dd>
	<dt>int x, y</dt>
		<dd>the coordinates for the tile in the containing room</dd>
		<dd>get_x(), get_y()</dd>
	<dt>Entity ent</dt>
		<dd>the entity in the tile, may be empty (null)</dd>
		<dd>get_entity(), set_entity(Entity ent)</dd>
</dl>

##### Member functions:  
<dl>
	<dt>void init(NodePath node, Room_Tile tile)</dt>
		<dd>initializes the tile, other functions (including get/set) will not work until init is called</dd>
	<dt>bool is_initialized()</dt>
		<dd>check if tile is initialized</dd>
</dl>

### Room_Map

##### Properties:  
<dl>
	<dt>Floor_Map floor</dt>
		<dd>the floor that the room resides in</dd>
		<dd>get_floor()</dd>
	<dt>Room_Tile** tiles</dt>
		<dd>a 2d array of tiles that the room contains</dd>
		<dd>get_tile(int x, int y)</dd>
	<dt>int x, y</dt>
		<dd>the coordinates for the room int the containing floor</dd>
		<dd>get_x(), get_y()</dd>
	<dt>int size_x, size_y</dt>
		<dd>the dimensions for the grid of tiles that the room contains</dd>
		<dd>get_size_x(), get_size_y()</dd>
	<dt>bool doors[4]</dt>
		<dd>stores whether or not there is a door in each direction. Uses constants up, down, left, right</dd>
		<dd>get_door(int dir), set_doors(bool up, bool down, bool left, bool right)</dd>
</dl>

##### Member functions:  
<dl>
	<dt>void init(Floor_Map floor, int x, int y, int size_x, int size_y)</dt>
		<dd>initializes the room, other functions (including get/set) will not work until init is called</dd>
	<dt>bool is_initialized()</dt>
		<dd>check if room is initialized</dd>
</dl>

### Floor_Map

##### Properties:  
<dl>
	<dt>Room_Map** rooms</dt>
		<dd>a 2d array of rooms that the floor contains</dd>
		<dd>get_room(int x, int y)</dd>
	<dt>int size_x, size_y</dt>
		<dd>the dimensions for the grid of rooms that the floor contains</dd>
		<dd>get_size_x(), get_size_y()</dd>
</dl>

##### Member functions:  
<dl>
	<dt>void init(int size_x, int size_y)</dt>
		<dd>initializes the floor, other functions (including get/set) will not work until init is called</dd>
	<dt>bool is_initialized()</dt>
		<dd>check if floor is initialized</dd>
</dl>

### Interpreter

##### Properties:  

##### Member functions:  
<dl>
	<dt>bool init(String code)</dt>
		<dd>initializes the interpreter with the user's code, other functions will not work until init is called. returns success</dd>
	<dt>bool is_initialized()</dt>
		<dd>check if interpreter is initialized</dd>
	<dt>bool run()</dt>
		<dd>Calls a function in the user's code named 'run()' returns success</dd>
	<dt>bool finalize()</dt>
		<dd>Stops the interpreter. Needed to prevent errors/memory leaks. returns success</dd>
	<dt>bool is_button_pressed(int button)</dt>
		<dd>Checks if the user pressed the specified button with their python code. button uses the constants up, down, left, right, use_arrow</dd>
</dl>

### Python Module

Use:
```Python
import cw

def run():
	#user code here. Each time the player-bot steps, this is called
```

##### Methods:
<dl>
	<dt>cw.press_up()</dt>
	<dt>cw.press_down()</dt>
	<dt>cw.press_left()</dt>
	<dt>cw.press_right()</dt>
	<dt>cw.press_use_arrow()</dt>
		<dd>User can call these to press a virtual button input for the bot</dd>
	<dt>cw.get_pos_x()</dt>
	<dt>cw.get_pos_y()</dt>
		<dd>User can call these to get the position of the bot in the current room</dd>
	<dt>cw.get_room_x()</dt>
	<dt>cw.get_room_y()</dt>
		<dd>User can call these to get the x and y coordinates of the current room in the floor</dd>
	<dt>bool cw.get_enemy_at(x, y)</dt>
		<dd>User can call these to determine if there is an enemy on the tile of the (x, y) coordinates of the room</dd>
	<dt>bool cw.get_door(dir)</dt>
		<dd>determines if there is a door in the current room in the specified direction. Takes "u", "d", "l", or "r" as dir</dd>
	<dt>bool cw.get_door_room(str dir, x, y)</dt>
		<dd>determines if there is a door in the specified (x, y) room in the specified direction. Takes "u", "d", "l", or "r" as dir</dd>
</dl>




