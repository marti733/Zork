# ECE30862_Zork

Inputs: Filename.xml

Structure:

MAP -> Room, item, container, creature
Room -> Description, item, trigger, border, name, creature, container
Item -> Name, writing, status, turnon
Container -> Name, item, status, accept, trigger
Creature -> Name, vulnerability, attack, trigger
Trigger -> Command, condition, type, print
Border -> Direction, name
Turnon -> Print, action
Condition -> Has, owner, object, status
Attack -> Condition, print, action


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
