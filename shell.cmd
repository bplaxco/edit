;	OS shell interface, MS-DOS and UNIX

store-procedure prompt
	set $discmd false
	end-of-file
	insert-string "shell% "
	set-mark
	set $discmd true
	unmark-buffer
!endm

store-procedure getline
	set $discmd false
	end-of-file
	!force backward-character
	exchange-point-and-mark
	copy-region
	set %shline $kill
	end-of-file
	set $discmd true
!endm

store-procedure execline
;	shell-command "echo command not found > shtmp"
 	shell-command &cat %shline " > shtmp"
	!force insert-file shtmp
!endm

;	prompt and execute a command

10	store-macro
	run getline
	!if &not &seq %shline ""
		run execline
	!endif
	run prompt
!endm

11	store-macro
	set $discmd false
	!if &seq $cbufname "*Shell*"
		bind-to-key execute-macro-10 ^M
		run prompt
	!else
		bind-to-key newline ^M
	!endif
	set $discmd true
!endm

store-procedure openshell
	set $discmd false
	bind-to-key execute-macro-11 M-FNX
	select-buffer "*Shell*"
	set $discmd true
!endm

	run openshell
