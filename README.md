# ECE30862_Zork

Inputs: Filename.xml

Structure:

Game -> Room, item*, container*, creature*, inventory, location, status
Room -> Description, item(s), trigger, border(s), name, creature(s), container(s), status, type
Item -> Name, writing*, status, turnon*, trigger*, description*
Container -> Name, item(s)*, status*, accept*, trigger*
Creature -> Name, vulnerability*, attack*, trigger*, description, status
Trigger -> Command, condition(s)*, type, print*, name, action*
Border -> Direction, name
Turnon -> Print*, action*
Condition -> Has, owner, object, status
Attack -> Condition, print, action

* Optional, but default values are assigned

Strings :
name
description
direction
status
writing
object
owner
has
type
command
print
action
accept
vulnerability

Assumptions:
1. If the turn on has no action just return without updating the item
2. If you want to quit without being at an exit type quit or q
3. For errors in user input just inform of incorrect input
