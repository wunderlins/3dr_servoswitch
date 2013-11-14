--[[
-- @title CD USB camera trigger

FIXME: description 

read:
http://chdk.wikia.com/wiki/USB_Remote_Cable
http://chdk.wikia.com/wiki/USB_Remote_V2#Scripting_Interface
--]]

treshold = 500
pw_recent = 0
pw_last   = 0

repeat
	-- TODO: figure out unit of pulse width
	pw_recent = get_usb_power() -- should return the pulse with, unit unknown
	
	if (pw_recent ~= 0 and pw_recent ~= pw_last) then
		pw_last = pw_recent
		print(pw_recent)
	end
	
	--[[
	if (pw_recent > treshold) then
		-- print( "shutting down " )
		shut_down()
		sleep(1500)
	end
	
	if (pw_recent < treshold) then
		shoot()
		sleep(50)
	end
	]]--
until (false)

--[[
function pre_focus()
   local focused = false
   local try = 1
   while not focused and try <= 5 do
      -- print("Pre-focus attempt " .. try)
      press("shoot_half")
      sleep(2000)
      if get_prop(18) > 0 then
	 focused = true
	 set_aflock(1)
      end
      release("shoot_half")
      sleep(500)
      try = try + 1
   end
   return focused
end

-- print( "VidUAV Started " )

Started = 0
-- print( "VidUAV loop " )
a = -1;
repeat
	aold = a
	a = get_usb_power()
	-- if (a ~= aold) then
	-- 	print("a = " .. a)
	-- end
	if (a>7) then
	   --      print( "shutting down " )

			shut_down()
			sleep(1500)
	end
	if (a>2) or (Started == 1) then
		if Started == 0 then
		-- 	print( "recording Started " )

			sleep(1500)
			Started = 1
			if focus_at_start then
			   if not pre_focus() then
			-- 	  print "Unable to reach pre-focus"
			   end
			end
			sleep(1000)

			press("video")
			sleep(2000)
			release("video")
   		end	
	end
until ( false )
-- print( "VidUAV ended " )

]]--
