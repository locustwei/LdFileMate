--[[
[����]:��������
[˵��]:����Ʊ������1����߻��䣬��������������2��%�����ҹɼ۴����ڣ�����3��Ԫʱ������
[Code]:��Ʊ����
[nPercent]:����������ٷֱ�%��
[nValue]:�ɼ۸��ڣ�Ԫ��
[nVolumn]:���������ɣ�
--]]

if Code==nil then
	return "Code = nil"
end

local p = StockData:new(Code)

if p.Hight == 0 then
	return "p.High = 0"
end

local n = (p.Current - p.High) / p.High        

if (p.Current �� nValue) and (n > nPercent) then
	return p:Sell(nVolumn)                    
else
	return "����������"
end