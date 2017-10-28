# Zork
Zork Game Project for UPC School: Master in Videogame Design and Development.
This is my implementation for the assignment of creating a text based adventure
game inspired in the classic Zork.

## How to play:

Execute the exe file and start typing!

The available commands are:

* LOOK: 
  * With 0 parameters: Look the actual room.
  * With 1 parameter:
    * "me" or "myself": Look at yourself
    * Name of an item in the room or your inventory.   
    
* NORT | SOUTH | WEST | EAST | UP | DOWN :
  * Move to the indicated direction.
  
* OPEN _target_ :
  * Open _target_ and get the item inside, if there's any.
  
* TAKE _target_ :
  * Take _target_ and add it to your inventory.
  
* DROP _target_ :
  * Drop _target_ from your inventory into the room.
  
* INVENTORY
  * Enumerate the items inside your inventory.
  
* TIME
  * How much time has passed.
  
* TALK _target_
  * Initiate dialogue with _target_ .
  
* USE _target1_ with/on _target2_
  * Tries to use _target1_ on _target2_.

* COMBINE _target1_ with _target2_
  * Puts an items inside another _target1_ on _target2_.
  
