


--[[
for k,v in pairs(_G) do
    local pstr = string.format("%s=%s",k,v);
    print(pstr);
    if type(v) == "table" and k ~= "_G" then
        for k2 in pairs(v) do
            local pstr = string.format("-----> %s.%s",k,k2);
            print(pstr);
        end
    end
end
]]--

--print(xxx);
-- data = 123;
-- data2 = "hello";
-- print("Test" .. Test);

function Test1(a,b)
    print("Test1", a,b);
    return a + b;
end

function Test2(A,B,C)
    print("Test2 Lua", A,B,C);
    return 111,"LUA", 333.6;
    
end
