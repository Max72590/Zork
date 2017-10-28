# Zork
Zork Game Project for UPC School: Master in Videogame Design and Development.
This is my implementation for the assignment of creating a text based adventure
game inspired in the classic Zork.

Done by me: Maximino Puncernau Margarit.

Link to the repository: https://github.com/Max72590/Zork/

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
  * How much time has passed since you were poisoned.
  
* TALK _target_
  * Initiate dialogue with _target_ .
  
* USE _target1_ with/on _target2_
  * Tries to use _target1_ on _target2_.

* COMBINE _target1_ with _target2_
  * Puts an items inside another _target1_ on _target2_.
  
## Guide / Walkthough :

Go WEST or EAST, then NORTH and take _House_key_ 

Go WEST or EAST and then SOUTH 

USE _House_key_ with _Entrance_lock_

Go NORTH

You're now poisoned, you have 20 minutes to finish the game.

TAKE _Jug_ (Optional: LOOK _Note_ or TAKE _Note_ and LOOK _Note_ to be aware that you're poisoned)

Go EAST and OPEN _Closed_window_

Go WEST and WEST again

USE _Water_key_ with _Locked_faucet_ and USE _Jug_ with _Faucet_

Go EAST and EAST again.

USE _Filled_Jug_ with _Fireplace_ , OPEN _Fireplace_box_ , USE _Blue_key_ with _Blue_lock_

Go NORTH, TAKE _Bell_ and TAKE _Wax_Figure_

Go SOUTH, WEST and WEST again, USE _Wax_figure_ with _Stove_ and USE _Green_key_ with _Green_lock_ and go NORTH

OPEN _Metal_box_ (or TAKE and OPEN _Metal_box_ ) and COMBINE _Bell_clapper_ with _Bell_

Go EAST and UP

USE _Bell_ with _Strange_lock_ and go SOUTH

TALK _Prisoner_

Write 2 to answer the first riddle.

Write 3 to answer the first riddle.

Write 2 to answer the first riddle.

Congratulations! You finished the game.
