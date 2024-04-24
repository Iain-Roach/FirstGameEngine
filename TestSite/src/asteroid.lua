local x = 1;
local y = 1;


function MoveX(s)
	return s;
end

function MoveY(z)
	return z;
end


function AsteroidWrapX(aX)
if aX>800 then return 0
end
if aX<0 then return 800
end

	return aX 
end

function AsteroidWrapY(aY)
if aY>600 then return 0
end
if aY<0 then return 600
end

	return aY
end




