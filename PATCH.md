# patch notes
---
# 8:00 AM, Apr 29
## general
- removed hunter buying, as they are no longer relevant to the current game's direction
## server
- added a death timeout for players
## client
- added dependencies and grammar rules for new parser

-- this means that death will cause you to be inactive for a small period of time
---
# 7:03 PM, Apr 27
## general
- equipment/equipping was fundamentally broken on all counts, and now works fully :)
- added admin/debug command for generating items
- combat is now much more verbose, returning information about procs, encounters, and monster health
## server
- changed item drop formula from `rand() % (100 - monster_level)` to `rand() % (100 - ((monster_level / 20) + 5)) * monster_count;
- fixed new players not spawning with correct database entries
- changed the way notifications happen for grantItem
## client
- removed einspect from help text
---
# 12:56 AM, Apr 27
## client
- added timestamps for messages
- fixed whispers requiring a message length of at least two words
- removed `einspect` -- now in order to inspect equipped gear, type "inspect {head, shoulders...}"
- updated `help` text with newer commands
- you can no longer delete the prompt arrow :)
