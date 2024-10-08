![screen1](ss.png)
![screen2](ss2.png)

# DWM Patches, Changes, and Docs

## Status Bar: DWMBlocks-Async
- Tried to create POSIX compliant scripts where I can and are as fast as I can manage to get them.  They use nawk(awk) for output since printf couldnt play nicely with dwmblocks.
- Volume script uses a pkill signal to update it, everything else runs on sane intervals

## /// Patches & Notes \\\
 - Actual Fullscreen - Fullscreens given window and hides anything behind it
 - Always Center - Always centers floating windows
 - Autostart - Adds autostart script
 - Awesomebar - Window Titles that act like the bar from AwesomeWM, fully mouse functionality
 - Bar Height - This has been moved to the new DPI scaling method of using fontheight + x
 - Bottomstack Layout - Integrated with pertag and gaps
 - Colorbar - Added more colors and new color for active tags
 - Dmenumatchtop - Dmenu follows the topbar/bottombar position
 - Dragmfact - MOD+SHIFT+Button 3 drags the size of the master
 - DWMBlocks Systray - Patch that integrates DWMBlocks well with systray as well as a version of the statuscolors patch
 - Float Border Color - Different border color if window is floating
 - Fix Transparent Borders - Colors ARGB border as full opaque even with compositor running
 - Focus on Click - Uses mouse clicks instead of sloppy focus on cursor entry/exit.  Did this one manually and kept code but commented it out. Sloppy focus is anti-suckless anyway imo.
 - Fullgaps Toggle - Integrated this with PerTag to have whatever gap on any tag
 - NoBorderFlicker - Sounded good, Chris Down knows what he's doing
 - No Monocle Borders - Disable Borders in monocle mode
 - Pertag - Preserves mostly everything on a per tag basis
 - Preserve on Restart - Keeps windows on their respective tag when restarting DWM
 - Quit Prompt - Simple quit prompt powered by Dmenu
 - Restartsig - MOD+SHIFT+R restarts DWM.
 - Rotate Stack - MOD+SHIFT+J/K rotates the window around the stack
 - Set Border Pixels - Increase and Decrease border pixels also integrated with PerTag
 - Shiftview Clients - MOD+TAB/MOD+SHIFT+TAB switches between active tags
 - Systray
 - Tilemovemouse - MOD+Button1 can drag a tiled window into any other position like awesome
 - Toggle Border - Toggles the border on a given window if needed
 - View on Tag - Switches Tags when sending a window to whatever tag
 - Winicon - Adds the win icon in the title field
 - View & Tag Adjacent - Ability to scroll thru workspaces regardless if active or empty with mousewheel or send windows to adjacent workspaces

## /// Other Misc Changes \\\
 - Edited the bar height to be 1 px larger to make a 1px border along the bottom of the bar for a cleaner look.  Had to edit monocle section as well.
 - Hacked around with the systray to get 1px bottom border working there as well, using 0px spacing with proper foreground and background colors makes this look seamless.
 - Added a dwmsystray hint to the systray so picom can recognize not to use shadows there.
 - Added dwm to picom to disable shadows on top bar.
 - Changed layout symbols
 - Created a Jgmenu when right clicking the root window or the title window
 - Mousewheel scrolls thru windows in the title window (including hidden windows from awesomebar)
 - Middleclick closes the current window
 - Adjusted rectangles to be smaller being drawn on tags
 - Removed rectangles in title window for floating clients
 - Removed restart option from quit prompt menu and just used restartsig patch instead for a keybind
 - Autostart file at $HOME/.local/share/dwm/autostart.sh

## /// 7-25-2024 and Forward Refinements \\\
 - Fixed Systray icon padding/spacing and coloring so it works correclty
 - Fixed 1px black bar under systray to be complete length of the screen
 - Fixed Monocle mode both with bar showing and not to be the right size window
 - Fixed mouse actions with Awesomebar to work actually like awesome now, simple middle click closes windows regardless of focus/minimized.
 - Changed spawn function to use spawn.h, stolen from Chris Titus and Luke Smith.
 - Various small improvements from the dwm repository
 - Added error message for weather dwmblocks
 - Added killall patch, which just kills all windows other than currently selected
 - Added refresh rate patch, no more 60fps
 - Fixed snap Y position to correct for 1px black line at bottom of the bar
 - Added Kanagawa colors'ish to config for some flavor
