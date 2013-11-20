sleep 1000

while 1
	do
	k = get_usb_power
	until k>0
		if k < 5 then gosub "ch1up"
		if k > 4 and k < 8 then gosub "ch1mid"
		if k > 7 and k < 11 then gosub "ch1down"
		if k > 10 and k < 14 then gosub "ch2up"
		if k > 13 and k < 17 then gosub "ch2mid"
		if k > 16 and k < 20 then gosub "ch2down"
		if k > 19 then print "error"
	wend
end
