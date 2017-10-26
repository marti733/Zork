# ECE30862_Zork

Inputs: Filename.xml

Structure:

Game -> Room, item, container, creature
x Room -> Description, item, trigger, border, name, creature, container, status, type
x Item -> Name, writing, status, turnon
x Container -> Name, item, status, accept, trigger
x Creature -> Name, vulnerability, attack, trigger
Trigger -> Command, condition, type, print
x Border -> Direction, name
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
