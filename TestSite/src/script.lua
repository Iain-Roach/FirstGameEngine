function MoveX(x)
if x<2 then
	return x;
end

function MoveY(y)
	return y;
end

function AsteroidWrapX(aX)
if aX>800 then return 0;
if aX<0 then return 800;

	return aX 
end

function AsteroidWrapY(aY)
if aY>600 then return 0
if aY<0 then return 600

	return aY
end