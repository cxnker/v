local Players, RunService, ReplicatedStorage, StarterGui = game:GetService("Players"), game:GetService("RunService"), game:GetService("ReplicatedStorage"), game:GetService("StarterGui")
local LocalPlayer = Players.LocalPlayer
local Character = LocalPlayer.Character or LocalPlayer.CharacterAdded:Wait()
local Humanoid, RootPart = Character:WaitForChild("Humanoid"), Character:WaitForChild("HumanoidRootPart")

local Lib = loadstring(game:HttpGet("https://github.com/cxnker/v/raw/main/l"))()
local Window = Lib:MakeWindow({
    Title = "Hexagon Hub 🃏 | Brookhaven 🏡RP",
    SubTitle = "by Roun95",
    SaveFolder = "HexData"
})

Window:AddMinimizeButton({
    Button = { Image = "rbxassetid://103422693243379", BackgroundTransparency = 0 },
    Corner = { CornerRadius = UDim.new(1,1) },
})

local Tab1 = Window:MakeTab({"Info", "info"})
local Tab2 = Window:MakeTab({"Player", "user"})
local Tab3 = Window:MakeTab({"Avatar", "shirt"})
local Tab4 = Window:MakeTab({"Customize", "brush"})
local Tab5 = Window:MakeTab({"Car/House", "star"})
local Tab6 = Window:MakeTab({"Troll", "bomb"})
local Tab7 = Window:MakeTab({"Scripts", "scroll"})
local Tab8 = Window:MakeTab({"Teleportes", "mappin"})

local function newNotification(title, message, icon, duration)
    StarterGui:SetCore("SendNotification",{
        Title = title,
        Text = message,
		Icon = icon or "",
        Duration = duration or 5
    })
end
--------------------------------------------------
			-- === Tab 1: Info === --
--------------------------------------------------
Tab1:AddSection({"》 Version 1.0"})
--------------------------------------------------
			-- === Tab 2: Player === --
--------------------------------------------------
Tab2:AddSection({"》 Player Character"})

Tab2:AddSlider({
    Name = "Speed",
    Min = 1,
    Max = 500,
    Increase = 1,
    Default = 16,
    Callback = function(Value)
        Humanoid.WalkSpeed = Value
    end
})

Tab2:AddSlider({
    Name = "Jump",
    Min = 1,
    Max = 500,
    Increase = 1,
    Default = 50,
    Callback = function(Value)
        Humanoid.JumpPower = Value
    end
})

Tab2:AddSlider({
    Name = "Gravity",
    Min = 1,
    Max = 500,
    Increase = 1,
    Default = 196,
    Callback = function(Value)
        Workspace.Gravity = Value
    end
})
 
local infjumpEnabled = false
game:GetService("UserInputService").JumpRequest:Connect(function()
	if infjumpEnabled then
      if Character and Character:FindFirstChild("Humanoid") then
		Character.Humanoid:ChangeState(Enum.HumanoidStateType.Jumping)
      end
   end
end)

Tab2:AddButton({
    Name = "Reset Status",
    Callback = function()
        Workspace.Gravity = 196.2
        Humanoid.JumpPower = 50
        Humanoid.WalkSpeed = 16
        infjumpEnabled = false
    end
})

Tab2:AddToggle({
	Name = "Infinite Jump",
    Default = false,
    Callback = function(Value)
       infjumpEnabled = Value
    end
})

Tab2:AddToggle({
    Name = "Anti Sit",
    Default = false,
    Callback = function(state)
        if state then
            antiSitEnabled = RunService.Heartbeat:Connect(function()
                if Humanoid then
                    Humanoid:SetStateEnabled(Enum.HumanoidStateType.Seated, false)
                    if Humanoid:GetState() == Enum.HumanoidStateType.Seated then
                        Humanoid:ChangeState(Enum.HumanoidStateType.Running)
                    end
                    if Humanoid.SeatPart then
                        Humanoid.Sit = false
                        Humanoid.SeatPart = nil
                    end
                end
            end)
        else
            if antiSitEnabled then antiSitEnabled:Disconnect() end
            if Humanoid then
                Humanoid:SetStateEnabled(Enum.HumanoidStateType.Seated, true)
            end
        end
    end
})

Tab2:AddToggle({
    Name = "Noclip",
    Default = true,
    Callback = function(v)
        noclipEnabled = v
    end
})

RunService.Stepped:Connect(function()
    if noclipEnabled and Character then
        for _, part in pairs(Character:GetDescendants()) do
            if part:IsA("BasePart") and part.CanCollide then
                part.CanCollide = false
            end
        end
	else
		if noclipEnabled then noclipEnabled:Disconnect() end
			for _, part in pairs(Character:GetDescendants()) do
				if part:IsA("BasePart") then
					part.CanCollide = true
				end
			end
		end
	end)
--------------------------------------------------
			-- === Tab 3: Avatar === --
--------------------------------------------------
Tab3:AddSection({"》 Copy Avatar"})
local Remotes = ReplicatedStorage.Remotes
local Wear, ChangeCharacterBody = Remotes.Wear, Remotes.ChangeCharacterBody

local PlayerValue
local Target = nil

local function GetPlayerNames()
    local playerNames = {}
    for _, player in ipairs(Players:GetPlayers()) do
        if player.Name ~= LocalPlayer.Name then
            table.insert(playerNames, player.Name)
        end
    end
    return playerNames
end

local updateList = Tab3:AddDropdown({
    Name = "Update list",
    Options = GetPlayerNames(),
    Default = "",
    Callback = function(playername)
        PlayerValue = playername
        Target = playername
    end
})

local function updatePlayers()
    updateList:Set(GetPlayerNames())
end
updatePlayers()

Tab3:AddButton({"Update list", function()
    updatePlayers()
end})

Players.PlayerAdded:Connect(updatePlayers)
Players.PlayerRemoving:Connect(updatePlayers)

Tab3:AddButton({
    Name = "Copy avatar",
    Callback = function()
        if not Target then return end

        local LChar = LocalPlayer.Character
        local TPlayer = Players:FindFirstChild(Target)

        if TPlayer and TPlayer.Character then
            local LHumanoid = LChar and LChar:FindFirstChildOfClass("Humanoid")
            local THumanoid = TPlayer.Character:FindFirstChildOfClass("Humanoid")
            if LHumanoid and THumanoid then

                local LDesc = LHumanoid:GetAppliedDescription()
                for _, acc in ipairs(LDesc:GetAccessories(true)) do
                    if acc.AssetId and tonumber(acc.AssetId) then
                        Wear:InvokeServer(tonumber(acc.AssetId))
                        task.wait(0.2)
                    end
                end
                if tonumber(LDesc.Shirt) then
                    Wear:InvokeServer(tonumber(LDesc.Shirt))
                    task.wait(0.2)
                end
                if tonumber(LDesc.Pants) then
                    Wear:InvokeServer(tonumber(LDesc.Pants))
                    task.wait(0.2)
                end
                if tonumber(LDesc.Face) then
                    Wear:InvokeServer(tonumber(LDesc.Face))
                    task.wait(0.2)
                end
                local PDesc = THumanoid:GetAppliedDescription()
                local argsBody = {
                    [1] = {
                        [1] = PDesc.Torso,
                        [2] = PDesc.RightArm,
                        [3] = PDesc.LeftArm,
                        [4] = PDesc.RightLeg,
                        [5] = PDesc.LeftLeg,
                        [6] = PDesc.Head
                    }
                }
                ChangeCharacterBody:InvokeServer(unpack(argsBody))
                task.wait(0.5)

                if tonumber(PDesc.Shirt) then
                    Wear:InvokeServer(tonumber(PDesc.Shirt))
                    task.wait(0.3)
                end
                if tonumber(PDesc.Pants) then
                    Wear:InvokeServer(tonumber(PDesc.Pants))
                    task.wait(0.3)
                end
                if tonumber(PDesc.Face) then
                    Wear:InvokeServer(tonumber(PDesc.Face))
                    task.wait(0.3)
                end
                for _, v in ipairs(PDesc:GetAccessories(true)) do
                    if v.AssetId and tonumber(v.AssetId) then
                        Wear:InvokeServer(tonumber(v.AssetId))
                        task.wait(0.3)
                    end
                end
                local SkinColor = TPlayer.Character:FindFirstChild("Body Colors")
                if SkinColor then
                    Remotes.ChangeBodyColor:FireServer(tostring(SkinColor.HeadColor))
                    task.wait(0.3)
                end
                if tonumber(PDesc.IdleAnimation) then
                    Wear:InvokeServer(tonumber(PDesc.IdleAnimation))
                    task.wait(0.3)
                end
            end
        end
    end
})

Tab3:AddSection({"》 3D Clothes"})

local clothes = {
    {"Black-Arm-Bandages-1-0", 11458078735},
    {"Black-Oversized-Warmers", 10789914680},
    {"Black-Oversized-Off-Shoulder-Hoodie", 18396592827},
    {"White-Oversized-Off-Shoulder-Hoodie", 18396754379},
    {"Left-Leg-Spikes", 10814325667}
}

for _, btn in ipairs(clothes) do
    Tab3:AddButton({
        btn[1],
        function()
			local args = {btn[2]}
            Wear:InvokeServer(unpack(args))
        end
    })
end

Tab3:AddSection({"》 Character Editor"})
Tab3:AddParagraph({"Adjust the proportions of your avatar for a better result"})

Tab3:AddButton({
    Name = "Invisible",
    Callback = function()
	ChangeCharacterBody:InvokeServer({
		[1] = 15312911732, -- Torso
		[2] = 14532583477, -- Right Arm
		[3] = 14532583469, -- Left Arm
		[4] = 14532583517, -- Right Leg
		[5] = 14532583483, -- Left Leg
		[6] = 134082579, -- Head
	})
	end
})

Tab3:AddButton({
    Name = "(Mini-Plushie) and Headless",
    Callback = function()
	ChangeCharacterBody:InvokeServer({
		[1] = 112722466960512,
		[2] = 76079756909323,
		[3] = 82598238110471,
		[4] = 107431241133468,
		[5] = 103380121023771,
		[6] = 134082579,
	})
	end
})

Tab3:AddButton({
    Name = "(S15-Thin-Hourglass) and Headless",
    Callback = function()
	ChangeCharacterBody:InvokeServer({
		[1] = 129543160215232,
		[2] = 133466157082146,
		[3] = 73001997018020,
		[4] = 128776848621889,
		[5] = 81547744637409,
		[6] = 134082579,
	})
	end
})

Tab3:AddButton({
    Name = "(inf15-Thin) and Headless",
    Callback = function()
	ChangeCharacterBody:InvokeServer({
		[1] = 92757812011061,
		[2] = 99519402284266,
		[3] = 115905570886697,
		[4] = 84418052877367,
		[5] = 124343282827669,
		[6] = 134082579,
	})
	end
})

Tab3:AddButton({
    Name = "(Blush-Fashion-Doll) and Headless",
    Callback = function()
	ChangeCharacterBody:InvokeServer({
		[1] = 115745153758680,
		[2] = 18839824209,
		[3] = 18839824132,
		[4] = 127241951574732,
		[5] = 118303475394830,
		[6] = 134082579,
	})
	end
})

Tab3:AddButton({
    Name = "[M] Girl Body and Headless",
    Callback = function()
	ChangeCharacterBody:InvokeServer({
		[1] = 114206707267907,
		[2] = 18839824209,
		[3] = 18839824132,
		[4] = 127241951574732,
		[5] = 118303475394830,
		[6] = 134082579,
	})
	end
})

Tab3:AddButton({
    Name = "[M] Boy Body and Headless",
    Callback = function()
        local args = {
            {
                2517207746,
                2517204456,
                4416788553,
                4416785861,
                32336059,
                15093053680
            }
        }
        ChangeCharacterBody:InvokeServer(unpack(args))
    end
})

Tab3:AddButton({
    Name = "[M] Girl Body V2",
    Callback = function()
	ChangeCharacterBody:InvokeServer({
		[1] = 114206707267907,
		[2] = 18839824209,
		[3] = 18839824132,
		[4] = 127968751428204,
		[5] = 101521138059051,
		[6] = 14970560459,
	})
	end
})

Tab3:AddButton({
    Name = "(Classic-Female-v2-Torso) and Headless",
    Callback = function()
	ChangeCharacterBody:InvokeServer({
		[1] = 4637265517,
		[2] = 0,
		[3] = 0,
		[4] = 0,
		[5] = 0,
		[6] = 134082579,
	})
	end
})

Tab3:AddButton({
    Name = "Headless/Korblox",
    Callback = function()
	ChangeCharacterBody:InvokeServer({
		[1] = 0,
		[2] = 0,
		[3] = 0,
		[4] = 139607718,
		[5] = 0,
		[6] = 134082579,
	})
	end
})

Tab3:AddButton({
    Name = "Headless",
    Callback = function()
	ChangeCharacterBody:InvokeServer({
		[1] = 0,
		[2] = 0,
		[3] = 0,
		[4] = 0,
		[5] = 0,
		[6] = 134082579,
	})
	end
})

Tab3:AddButton({
    Name = "ROBLOX-Girl-Torso and Skelly Right Leg/Headless",
    Callback = function()
	ChangeCharacterBody:InvokeServer({
    	[1] = 48474356,
    	[2] = 0,
		[3] = 0,
		[4] = 14547141130,
	 	[5] = 0,
		[6] = 134082579,
	})
    end
})
Tab3:AddSection({"》 Animations"})

Tab3:AddButton({
    Name = "(adidas-Community-Animation-Pack) Animation",
    Callback = function()
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(123695349157584)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(93993406355955)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(106810508343012)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(106537993816942)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(126354114956642)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(124765145869332)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(115715495289805)
task.wait(0.3)
	end
})

Tab3:AddButton({
    Name = "(adidas-Sports-Animation-Pack) Animation",
    Callback = function()
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(18538170170)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(18538164337)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(18538150608)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(18538153691)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(18538133604)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(18538158932)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(18538146480)
task.wait(0.3)
	end
})

Tab3:AddButton({
    Name = "(Catwalk-Glam-Animation-Pack-by-e.l.f.) Animation",
    Callback = function()
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(104741822987331)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(72706690305027)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(101279640971758)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(138641066989023)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(75036746190467)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(112231179705221)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(103190462987721)
task.wait(0.3)
	end
})

Tab3:AddButton({
    Name = "(Bold-Animation-Pack-by-e.l.f.) Animation",
    Callback = function()
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(16744204409)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(16744207822)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(16744209868)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(16744212581)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(16744214662)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(16744217055)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(16744219182)
task.wait(0.3)
	end
})

Tab3:AddButton({
    Name = "(No-Boundaries-Animation-Pack-by-Walmart) Animation",
    Callback = function()
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(18755919175)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(18755922352)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(18755930927)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(18755925411)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(18755933883)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(18755938274)
task.wait(0.3)
	game:GetService("ReplicatedStorage").Remotes.Wear:InvokeServer(18755942776)
task.wait(0.3)
	end
})

Tab3:AddSection({"》 Custom Body Parts (Experimental)"})
Tab3:AddParagraph({"Enter the ID of the item you want to use"})

Tab3:AddTextBox({
    Name = "Torso",
    Description = "Enter Torso ID",
    PlaceholderText = "Victory Hub",
    Callback = function(value1)
	ChangeCharacterBody:InvokeServer({
		[1] = value1,
		[2] = 0,
		[3] = 0,
		[4] = 0,
		[5] = 0,
		[6] = 134082579,
	})
    end
})

Tab3:AddTextBox({
    Name = "Right Arm",
    Description = "Enter Right Arm ID",
    PlaceholderText = "Victory Hub",
    Callback = function(value2)
	ChangeCharacterBody:InvokeServer({
		[1] = 0,
		[2] = value2,
		[3] = 0,
		[4] = 0,
		[5] = 0,
		[6] = 134082579,
	})
    end
})

Tab3:AddTextBox({
    Name = "Left Arm",
    Description = "Enter Left Arm ID",
    PlaceholderText = "Victory Hub",
    Callback = function(value3)
	ChangeCharacterBody:InvokeServer({
		[1] = 0,
		[2] = 0,
		[3] = value3,
		[4] = 0,
		[5] = 0,
		[6] = 134082579,
	})
    end
})

Tab3:AddTextBox({
    Name = "Right Leg",
    Description = "Enter Right Leg ID",
    PlaceholderText = "Victory Hub",
    Callback = function(value4)
	ChangeCharacterBody:InvokeServer({
		[1] = 0,
		[2] = 0,
		[3] = 0,
		[4] = value4,
		[5] = 0,
		[6] = 134082579,
	})
    end
})

Tab3:AddTextBox({
    Name = "Left Leg",
    Description = "Enter Left Leg ID",
    PlaceholderText = "Victory Hub",
    Callback = function(value5)
	ChangeCharacterBody:InvokeServer({
		[1] = 0,
		[2] = 0,
		[3] = 0,
		[4] = 0,
		[5] = value5,
		[6] = 134082579,
	})
    end
})

Tab3:AddTextBox({
    Name = "Head",
    Description = "Enter Head ID",
    PlaceholderText = "Victory Hub",
    Callback = function(value6)
	ChangeCharacterBody:InvokeServer({
		[1] = 0,
		[2] = 0,
		[3] = 0,
		[4] = 0,
		[5] = 0,
		[6] = value6,
	})
    end
})
--------------------------------------------------
			-- === Tab 4: Customize === --
--------------------------------------------------
Tab4:AddSection({"》 Customize"})

local nameColor = false

Tab4:AddToggle({
    Name = "Name RGB",
    Default = false,
    Callback = function(value)
        nameColor = value
    end
})

local putColors = {
    Color3.fromRGB(0, 0, 0),
    Color3.fromRGB(255, 255, 255)
}
	
spawn(function()
    while true do
        if nameColor then
            local randomColor = putColors[math.random(#putColors)]
            ReplicatedStorage.RE["1RPNam1eColo1r"]:FireServer("PickingRPNameColor", randomColor)
        end
        wait(0.3)
    end
end)
--------------------------------------------------
			-- === Tab 5: Car/House === --
--------------------------------------------------
Tab5:AddSection({"》 House"})

Tab5:AddButton({
    Name = "Unban all houses",
    Callback = function()
        local successCount = 0
        local failCount = 0
        for i = 1, 37 do
            local bannedBlockName = "BannedBlock" .. i
            local bannedBlock = Workspace:FindFirstChild(bannedBlockName, true)
            if bannedBlock then
                local success, _ = pcall(function()
                    bannedBlock:Destroy()
                end)
                if success then
                    successCount = successCount + 1
                else
                    failCount = failCount + 1
                end
            end
        end
        for _, house in pairs(Workspace:GetDescendants()) do
            if house.Name:match("BannedBlock") then
                local success, _ = pcall(function()
                    house:Destroy()
                end)
                if success then
                    successCount = successCount + 1
                else
                    failCount = failCount + 1
                end
            end
        end
        if successCount > 0 then
			newNotification("Success", "Unbanned from " .. successCount .. " houses")
        end
        if failCount > 0 then
			newNotification("Failed", "Not unbanned from " .. failCount .. " houses")
        end
        if successCount == 0 and failCount == 0 then
			newNotification("Warn", "Not banned houses find")
        end
    end
})

Tab5:AddSection({"》 Spawm Premium Cars"})

Tab5:AddButton({
    Name = "Hummer",
    Callback = function()
        ReplicatedStorage.RE["1Ca1r"]:FireServer(table.unpack({[1]="PickingCar", [2]="Hummer"}))
    end
})
Tab5:AddButton({
    Name = "Roadster",
    Callback = function()
        ReplicatedStorage.RE["1Ca1r"]:FireServer(table.unpack({[1]="PickingCar", [2]="Roadster"}))
    end
})
Tab5:AddButton({
    Name = "Bugatti",
    Callback = function()
        ReplicatedStorage.RE["1Ca1r"]:FireServer(table.unpack({[1]="PickingCar", [2]="Bugatti"}))
    end
})
Tab5:AddButton({
    Name = "CyberTruck",
    Callback = function()
        ReplicatedStorage.RE["1Ca1r"]:FireServer(table.unpack({[1]="PickingCar", [2]="CyberTruck"}))
    end
})
Tab5:AddButton({
    Name = "CopLamborgini",
    Callback = function()
        ReplicatedStorage.RE["1Ca1r"]:FireServer(table.unpack({[1]="PickingCar", [2]="CopLamborgini"}))
    end
})
Tab5:AddButton({
    Name = "Buggy",
    Callback = function()
        ReplicatedStorage.RE["1Ca1r"]:FireServer(table.unpack({[1]="PickingCar", [2]="Buggy"}))
    end
})
Tab5:AddButton({
    Name = "GoKartVPass",
    Callback = function()
        ReplicatedStorage.RE["1Ca1r"]:FireServer(table.unpack({[1]="PickingCar", [2]="GoKartVPass"}))
    end
})
Tab5:AddButton({
    Name = "BatMobile",
    Callback = function()
        ReplicatedStorage.RE["1Ca1r"]:FireServer(table.unpack({[1]="PickingCar", [2]="BatMobile"}))
    end
})
Tab5:AddButton({
    Name = "Formula1",
    Callback = function()
        ReplicatedStorage.RE["1Ca1r"]:FireServer(table.unpack({[1]="PickingCar", [2]="Formula1"}))
    end
})
Tab5:AddButton({
    Name = "SuperCar",
    Callback = function()
        ReplicatedStorage.RE["1Ca1r"]:FireServer(table.unpack({[1]="PickingCar", [2]="SuperCar"}))
    end
})
Tab5:AddButton({
    Name = "HummerLimo",
    Callback = function()
        ReplicatedStorage.RE["1Ca1r"]:FireServer(table.unpack({[1]="PickingCar", [2]="HummerLimo"}))
    end
})
Tab5:AddButton({
    Name = "Ferrari",
    Callback = function()
        ReplicatedStorage.RE["1Ca1r"]:FireServer(table.unpack({[1]="PickingCar", [2]="Ferrari"}))
    end
})

Tab5:AddSection({"》 Car Customize"})

local WheelLoop = false

Tab5:AddToggle({
    Name = "Auto Wheel Decal",
    Default = false,
    Callback = function(Value)
        WheelLoop = Value
        if WheelLoop then
            spawn(function()
                while WheelLoop do
                    pcall(function()
                        ReplicatedStorage:WaitForChild("Remotes"):WaitForChild("SetWheelDecal"):InvokeServer()
                    end)
                    wait(0.5)
                end
            end)
        end
    end
})

local SuspensionLoop = false

Tab5:AddToggle({
    Name = "Suspension Loop",
    Default = false,
    Callback = function(v)
        SuspensionLoop = v
        if SuspensionLoop then
            spawn(function()
                while SuspensionLoop do
                    ReplicatedStorage:WaitForChild("Remotes"):WaitForChild("SetNextSuspensionHeight"):InvokeServer()
                    wait(0.2)
                end
            end)
        end
    end
})
--------------------------------------------------
			-- === Tab 6: Troll === --
--------------------------------------------------
Tab6:AddSection({"》 Troll Options"})

local selectedPlayerName = nil
local headsitActive = false
local function headsitOnPlayer(targetPlayer)
    if not targetPlayer.Character or not targetPlayer.Character:FindFirstChild("Head") then
        warn("Character has no Head")
        return false
    end
    local targetHead = targetPlayer.Character.Head
    local localRoot = Character:FindFirstChild("HumanoidRootPart")
    if not localRoot then
        warn("Character has no HumanoidRootPart")
        return false
    end
    localRoot.CFrame = targetHead.CFrame * CFrame.new(0, 2.2, 0)
    for _, v in pairs(localRoot:GetChildren()) do
        if v:IsA("WeldConstraint") then
            v:Destroy()
        end
    end
    local weld = Instance.new("WeldConstraint")
    weld.Part0 = localRoot
    weld.Part1 = targetHead
    weld.Parent = localRoot
    if Humanoid then
        Humanoid.Sit = true
    end
    print("Headsit activated on " .. targetPlayer.Name)
    return true
end

local function removeHeadsit()
    local localRoot = Character:FindFirstChild("HumanoidRootPart")
    if localRoot then
        for _, v in pairs(localRoot:GetChildren()) do
            if v:IsA("WeldConstraint") then
                v:Destroy()
            end
        end
    end
    if Humanoid then
        Humanoid.Sit = false
    end
    print("Headsit disabled")
end

local function findPlayerByPartialName(partial)
    partial = partial:lower()
    for _, player in pairs(Players:GetPlayers()) do
        if player ~= localPlayer and player.Name:lower():sub(1, #partial) == partial then
            return player
        end
    end
    return nil
end

local function headsitNotify(player)
	newNotification("Player selected", player.Name .. " selected", Players:GetUserThumbnailAsync(player.UserId, Enum.ThumbnailType.HeadShot, Enum.ThumbnailSize.Size100x100))
end

Tab6:AddTextBox({
    Name = "Headsit Player",
    Description = "Enter part of the player name",
    PlaceholderText = "ex: Rou → Roun95",
    Callback = function(Value)
    local foundPlayer = findPlayerByPartialName(Value)
        if foundPlayer then
            selectedPlayerName = foundPlayer.Name
            headsitNotify(foundPlayer)
        else
            warn("No player found with that name")
        end
    end
})

Tab6:AddButton({"Enable Headsit", function()
    if not selectedPlayerName then
        return
    end
    if not headsitActive then
        local target = Players:FindFirstChild(selectedPlayerName)
        if target and headsitOnPlayer(target) then
			headsitActive = true
        end
    else
        removeHeadsit()
		headsitActive = false
    end
end
})

Tab6:AddToggle({
    Name = "ESP Players",
    Default = false,
    Callback = function(Enabled)
        local function CreateESP(Player)
            if not Player.Character or not Player.Character:FindFirstChild("HumanoidRootPart") then return end

            local Character = Player.Character
            local HRP = Character.HumanoidRootPart

            local ESP = Instance.new("BillboardGui")
            ESP.Name = "ESP_" .. Player.Name
            ESP.Adornee = HRP
            ESP.Size = UDim2.new(0, 100, 0, 50)
            ESP.StudsOffset = Vector3.new(0, 2.5, 0)
            ESP.AlwaysOnTop = true
            ESP.Parent = HRP

            local NameLabel = Instance.new("TextLabel")
            NameLabel.Name = "NameLabel"
			NameLabel.BackgroundTransparency = 1
			NameLabel.Text = Player.Name
			NameLabel.TextColor3 = Color3.fromRGB(220, 220, 220)
	        NameLabel.Size = UDim2.new(1, 0, 0, 20)
            NameLabel.Parent = ESP
        end

        for _, Player in pairs(Players:GetPlayers()) do
            if Player ~= LocalPlayer and Player.Character then
                local HRP = Player.Character:FindFirstChild("HumanoidRootPart")
                if HRP then
                    local OldESP = HRP:FindFirstChild("ESP_" .. Player.Name)
                    if OldESP then
                        OldESP:Destroy()
                    end
                end
            end
        end

        if Enabled then
            for _, Player in pairs(Players:GetPlayers()) do
                if Player ~= LocalPlayer then
                    Player.CharacterAdded:Connect(function()
                        CreateESP(Player)
                    end)
                    if Player.Character then
                        CreateESP(Player)
                    end
                end
            end

            Players.PlayerAdded:Connect(function(Player)
                Player.CharacterAdded:Connect(function()
                    CreateESP(Player)
                end)
            end)
        end
    end
})

Tab6:AddSection({"》 Admin Options"})

Tab6:AddButton({
    Name = "[Click] Admin Fling (Tool)",
    Callback = function()
        local jogadores = game:GetService("Players")
        local rep = game:GetService("ReplicatedStorage")
        local mundo = game:GetService("Workspace")
        local entrada = game:GetService("UserInputService")
        local cam = mundo.CurrentCamera
        local eu = jogadores.LocalPlayer

        local NOME_FERRAMENTA = "Admin Fling"
        local ferramentaEquipada = false

        local mochila = eu:WaitForChild("Backpack")

        for _, ferramentaExistente in pairs(mochila:GetChildren()) do
            if ferramentaExistente:IsA("Tool") and ferramentaExistente.Name:lower():find("fling") then
                ferramentaExistente.Name = "Admin Fling"
            end
        end

        if not mochila:FindFirstChild(NOME_FERRAMENTA) then
            local ferramenta = Instance.new("Tool")
            ferramenta.Name = NOME_FERRAMENTA
            ferramenta.RequiresHandle = true
            ferramenta.CanBeDropped = false

            local handle = Instance.new("Part")
            handle.Name = "Handle"
            handle.Size = Vector3.new(1, 1, 1)
            handle.Transparency = 1
            handle.Parent = ferramenta

            local decal = Instance.new("Decal")
            decal.Texture = "rbxassetid://775552544"
            decal.Face = Enum.NormalId.Front
            decal.Parent = handle

            ferramenta.Equipped:Connect(function()
                ferramentaEquipada = true
            end)

            ferramenta.Unequipped:Connect(function()
                ferramentaEquipada = false
            end)

            ferramenta.Parent = mochila
        end

        local function FlingBall(target)
            local player = jogadores.LocalPlayer
            local character = player.Character or player.CharacterAdded:Wait()
            local humanoid = character:WaitForChild("Humanoid")
            local hrp = character:WaitForChild("HumanoidRootPart")
            local backpack = player:WaitForChild("Backpack")
            local ServerBalls = mundo:WaitForChild("WorkspaceCom"):WaitForChild("001_SoccerBalls")

            local function GetBall()
                if not backpack:FindFirstChild("SoccerBall") and not character:FindFirstChild("SoccerBall") then
                    rep.RE:FindFirstChild("1Too1l"):InvokeServer("PickingTools", "SoccerBall")
                end
                repeat task.wait() until backpack:FindFirstChild("SoccerBall") or character:FindFirstChild("SoccerBall")
                local ballTool = backpack:FindFirstChild("SoccerBall")
                if ballTool then ballTool.Parent = character end
                repeat task.wait() until ServerBalls:FindFirstChild("Soccer" .. player.Name)
                return ServerBalls:FindFirstChild("Soccer" .. player.Name)
            end

            local Ball = ServerBalls:FindFirstChild("Soccer" .. player.Name) or GetBall()
            Ball.CanCollide = false
            Ball.Massless = true
            Ball.Transparency = 1             -- BOLA INVISÍVEL
            Ball.CustomPhysicalProperties = PhysicalProperties.new(0.0001, 0, 0)

            if target ~= player then
                local tchar = target.Character
                if tchar and tchar:FindFirstChild("HumanoidRootPart") and tchar:FindFirstChild("Humanoid") then
                    local troot = tchar.HumanoidRootPart
                    local thum = tchar.Humanoid
                    if Ball:FindFirstChildWhichIsA("BodyVelocity") then
                        Ball:FindFirstChildWhichIsA("BodyVelocity"):Destroy()
                    end
                    local bv = Instance.new("BodyVelocity")
                    bv.Name = "FlingPower"
                    bv.Velocity = Vector3.new(9e8, 9e8, 9e8)
                    bv.MaxForce = Vector3.new(math.huge, math.huge, math.huge)
                    bv.P = 9e900
                    bv.Parent = Ball
                    mundo.CurrentCamera.CameraSubject = thum

                    repeat
                        if troot.Velocity.Magnitude > 0 then
                            local pos = troot.Position + (troot.Velocity / 1.5)
                            Ball.CFrame = CFrame.new(pos)
                            Ball.Orientation += Vector3.new(45, 60, 30)
                        else
                            for _, v in pairs(tchar:GetChildren()) do
                                if v:IsA("BasePart") and v.CanCollide and not v.Anchored then
                                    Ball.CFrame = v.CFrame
                                    task.wait(1/6000)
                                end
                            end
                        end
                        task.wait(1/6000)
                    until troot.Velocity.Magnitude > 1000 or thum.Health <= 0 or not tchar:IsDescendantOf(mundo) or target.Parent ~= jogadores

                    mundo.CurrentCamera.CameraSubject = humanoid
                end
            end
        end

        entrada.TouchTap:Connect(function(toques, processado)
            if not ferramentaEquipada or processado then return end
            local pos = toques[1]
            local raio = cam:ScreenPointToRay(pos.X, pos.Y)
            local hit = mundo:Raycast(raio.Origin, raio.Direction * 1000)
            if hit and hit.Instance then
                local modelo = hit.Instance:FindFirstAncestorOfClass("Model")
                local jogador = jogadores:GetPlayerFromCharacter(modelo)
                if jogador and jogador ~= eu then
                    FlingBall(jogador)
                end
            end
        end)
    end
})

Tab6:AddButton({
    Name = "[Click] Admin Sword (Tool)",
    Callback = function()
local Players = game:GetService("Players")
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local RunService = game:GetService("RunService")
local LocalPlayer = Players.LocalPlayer

local buggedPlayers = {}
local bugConnections = {}
local Remote = ReplicatedStorage.RE:FindFirstChild("1Gu1n")

local tool = Instance.new("Tool")
tool.Name = "Admin Sword"
tool.RequiresHandle = true
tool.CanBeDropped = true

local handle = Instance.new("Part")
handle.Name = "Handle"
handle.Size = Vector3.new(0.1, 0.1, 0.1)
handle.Massless = true
handle.Anchored = false
handle.CanCollide = false
handle.Transparency = 0.5
handle.Color = Color3.fromRGB(255, 0, 0)
local mesh = Instance.new("SpecialMesh", handle)
mesh.MeshType = Enum.MeshType.Sphere
mesh.Scale = Vector3.new(0.05, 0.05, 0.05)
handle.Parent = tool

local function bugPlayer(targetPlayer)
    if not Remote then
        newNotification("⚠️ Warn", "Remote not found")
        return
    end
    
    if not targetPlayer or not targetPlayer.Character then
        newNotification("⚠️ Warn", "Invalid player")
        return
    end
    
    local playerName = targetPlayer.Name
    
    if buggedPlayers[playerName] then
        if bugConnections[playerName] then
            bugConnections[playerName]:Disconnect()
            bugConnections[playerName] = nil
        end
        buggedPlayers[playerName] = nil
        newNotification("🔓 Unapplied Bug", playerName .. " debugged player")
        return
    end
    
    buggedPlayers[playerName] = true
    newNotification("🔨 Bug Applied", playerName .. " was bugged")
    
    bugConnections[playerName] = RunService.Stepped:Connect(function()
        local target = Players:FindFirstChild(playerName)
        if not target or not target.Character or not target.Character:FindFirstChild("HumanoidRootPart") then
            if bugConnections[playerName] then
                bugConnections[playerName]:Disconnect()
                bugConnections[playerName] = nil
            end
            buggedPlayers[playerName] = nil
            return
        end

        local crazyVector = Vector3.new(
            math.random(1e25, 1e25),
            math.random(1e25, 1e25),
            math.random(1e25, 1e25)
        )

        local args = {
            [1] = target.Character.HumanoidRootPart,
            [2] = target.Character.HumanoidRootPart,
            [3] = crazyVector,
            [4] = target.Character.HumanoidRootPart.Position,
            [5] = LocalPlayer.Backpack:FindFirstChild("Assault") and LocalPlayer.Backpack.Assault.GunScript_Local:FindFirstChild("MuzzleEffect"),
            [6] = LocalPlayer.Backpack:FindFirstChild("Assault") and LocalPlayer.Backpack.Assault.GunScript_Local:FindFirstChild("HitEffect"),
            [7] = 3000,
            [8] = 3000,
            [9] = { [1] = false },
            [10] = {
                [1] = 10000,
                [2] = Vector3.new(3000, 3000, 3000),
                [3] = BrickColor.new(29),
                [4] = 0.05,
                [5] = Enum.Material.SmoothPlastic,
                [6] = 0.05
            },
            [11] = true,
            [12] = false
        }

        Remote:FireServer(unpack(args))
    end)
end

local function getPlayerFromMouse(mouse)
    local target = mouse.Target
    if not target then return nil end
    local character = target.Parent
    while character and not character:FindFirstChild("Humanoid") do
        character = character.Parent
    end
    if character and character:FindFirstChild("Humanoid") then
        return Players:GetPlayerFromCharacter(character)
    end
    return nil
end

tool.Equipped:Connect(function(mouse)
    local character = tool.Parent
    if character and character:FindFirstChild("Humanoid") and character.Humanoid.RigType == Enum.HumanoidRigType.R15 then

    game:GetService("ReplicatedStorage"):WaitForChild("Remotes"):WaitForChild("Wear"):InvokeServer(12928981934) -- Tool Model

        mouse.Button1Down:Connect(function()
            local humanoid = character:FindFirstChildOfClass("Humanoid")
            local animator = humanoid and humanoid:FindFirstChildOfClass("Animator")
            if animator then
                local anim = Instance.new("Animation")
                anim.AnimationId = "rbxassetid://2410679501"
                local track = animator:LoadAnimation(anim)
                track:Play()
            end
            
            local targetPlayer = getPlayerFromMouse(mouse)
            if targetPlayer and targetPlayer ~= LocalPlayer then
                bugPlayer(targetPlayer)
            else
                newNotification("⚠️ Warn", "Click on a player to apply/remove bug")
            end
        end)
        
        newNotification("📤 Admin Sword equipped", "Click on a player to apply/remove bug")
    end
end)

tool.Unequipped:Connect(function()
    game:GetService("ReplicatedStorage"):WaitForChild("Remotes"):WaitForChild("Wear"):InvokeServer(12928981934) -- Tool Model
    newNotification("​📥 ​Admin Sword saved", "Unequipped tool")
end)

Players.PlayerRemoving:Connect(function(player)
    local playerName = player.Name
    if bugConnections[playerName] then
        bugConnections[playerName]:Disconnect()
        bugConnections[playerName] = nil
    end
    buggedPlayers[playerName] = nil
end)

LocalPlayer.Chatted:Connect(function(message)
    if message:lower() == "/stopallbugs" then
        for _, connection in pairs(bugConnections) do
            if connection then connection:Disconnect() end
        end
        bugConnections = {}
        buggedPlayers = {}
        newNotification("🛑 All bugs removed", "All players were debugged")
    elseif message:lower() == "/buggedlist" then
        local count = 0
        for _ in pairs(buggedPlayers) do count = count + 1 end
        newNotification("📋 Player list", count > 0 and (count.." players bugged") or "No bugged players were found")
    end
end)

tool.Parent = LocalPlayer.Backpack
newNotification("✅ Admin Sword enable", "Added tool, Use /stopallbugs to stop all bugs, and /buggedlist for view listed players")
    end
})

Tab6:AddButton({
    Name = "[Click] Kill Couch (Tool)",
    Callback = function()

local jogadores = game:GetService("Players")
local rep = game:GetService("ReplicatedStorage")
local loop = game:GetService("RunService")
local mundo = game:GetService("Workspace")
local entrada = game:GetService("UserInputService")

local eu = jogadores.LocalPlayer
local cam = mundo.CurrentCamera

local NOME_FERRAMENTA = "Kill Couch"
local ferramentaEquipada = false
local nomeAlvo = nil
local loopTP = nil
local sofaEquipado = false
local base = nil
local posInicial = nil
local raiz = nil

local mochila = eu:WaitForChild("Backpack")
if not mochila:FindFirstChild(NOME_FERRAMENTA) then
	local ferramenta = Instance.new("Tool")
	ferramenta.Name = NOME_FERRAMENTA
	ferramenta.RequiresHandle = false
	ferramenta.CanBeDropped = false

	ferramenta.Equipped:Connect(function()
		ferramentaEquipada = true
	end)

	ferramenta.Unequipped:Connect(function()
		ferramentaEquipada = false
		nomeAlvo = nil
		limparSofa()
	end)

	ferramenta.Parent = mochila
end

function limparSofa()
	if loopTP then
		loopTP:Disconnect()
		loopTP = nil
	end

	if sofaEquipado then
		local boneco = eu.Character
		if boneco then
			local sofa = boneco:FindFirstChild("Couch")
			if sofa then
				sofa.Parent = eu.Backpack
				sofaEquipado = false
			end
		end
	end

	if base then
		base:Destroy()
		base = nil
	end

	if getgenv().AntiSit then
		getgenv().AntiSit:Set(false)
	end

	local humano = eu.Character and eu.Character:FindFirstChildOfClass("Humanoid")
	if humano then
		humano:SetStateEnabled(Enum.HumanoidStateType.Physics, true)
		humano:ChangeState(Enum.HumanoidStateType.GettingUp)
	end

	if posInicial and raiz then
		raiz.CFrame = posInicial
		posInicial = nil
	end
end

function pegarSofa()
	local boneco = eu.Character
	if not boneco then return end
	local mochila = eu.Backpack

	if not mochila:FindFirstChild("Couch") and not boneco:FindFirstChild("Couch") then
		local args = { "PickingTools", "Couch" }
		rep.RE["1Too1l"]:InvokeServer(unpack(args))
		task.wait(0.1)
	end

	local sofa = mochila:FindFirstChild("Couch") or boneco:FindFirstChild("Couch")
	if sofa then
		sofa.Parent = boneco
		sofaEquipado = true
	end
end

function posAleatoriaAbaixo(boneco)
	local rp = boneco:FindFirstChild("HumanoidRootPart")
	if not rp then return Vector3.new() end
	local offset = Vector3.new(math.random(-2, 2), -5.1, math.random(-2, 2))
	return rp.Position + offset
end

function tpAbaixo(alvo)
	if not alvo or not alvo.Character or not alvo.Character:FindFirstChild("HumanoidRootPart") then return end

	local meuBoneco = eu.Character
	local minhaRaiz = meuBoneco and meuBoneco:FindFirstChild("HumanoidRootPart")
	local humano = meuBoneco and meuBoneco:FindFirstChildOfClass("Humanoid")

	if not minhaRaiz or not humano then return end

	humano:SetStateEnabled(Enum.HumanoidStateType.Physics, false)

	if not base then
		base = Instance.new("Part")
		base.Size = Vector3.new(10, 1, 10)
		base.Anchored = true
		base.CanCollide = true
		base.Transparency = 0.5
		base.Parent = mundo
	end

	local destino = posAleatoriaAbaixo(alvo.Character)
	base.Position = destino
	minhaRaiz.CFrame = CFrame.new(destino)

	humano:SetStateEnabled(Enum.HumanoidStateType.Physics, true)
end

function arremessarComSofa(alvo)
	if not alvo then return end
	nomeAlvo = alvo.Name
	local boneco = eu.Character
	if not boneco then return end

	posInicial = boneco:FindFirstChild("HumanoidRootPart") and boneco.HumanoidRootPart.CFrame
	raiz = boneco:FindFirstChild("HumanoidRootPart")
	pegarSofa()

	loopTP = loop.Heartbeat:Connect(function()
		local alvoAtual = jogadores:FindFirstChild(nomeAlvo)
		if not alvoAtual or not alvoAtual.Character or not alvoAtual.Character:FindFirstChild("Humanoid") then
			limparSofa()
			return
		end
		if getgenv().AntiSit then
			getgenv().AntiSit:Set(true)
		end
		tpAbaixo(alvoAtual)
	end)

	task.spawn(function()
		local alvoAtual = jogadores:FindFirstChild(nomeAlvo)
		while alvoAtual and alvoAtual.Character and alvoAtual.Character:FindFirstChild("Humanoid") do
			task.wait(0.05)
			if alvoAtual.Character.Humanoid.SeatPart then
				local buraco = CFrame.new(265.46, -450.83, -59.93)
				alvoAtual.Character.HumanoidRootPart.CFrame = buraco
				eu.Character.HumanoidRootPart.CFrame = buraco
				task.wait(0.4)
				limparSofa()
				task.wait(0.2)
				if posInicial then
					eu.Character.HumanoidRootPart.CFrame = posInicial
				end
				break
			end
		end
	end)
end

entrada.TouchTap:Connect(function(toques, processado)
	if not ferramentaEquipada or processado then return end
	local pos = toques[1]
	local raio = cam:ScreenPointToRay(pos.X, pos.Y)
	local hit = mundo:Raycast(raio.Origin, raio.Direction * 1000)
	if hit and hit.Instance then
		local modelo = hit.Instance:FindFirstAncestorOfClass("Model")
		local jogador = jogadores:GetPlayerFromCharacter(modelo)
		if jogador and jogador ~= eu then
			arremessarComSofa(jogador)
		end
	end
end)
end
})

Tab6:AddButton({
    Name = "Annoy server",
    Callback = function()
        local RE = ReplicatedStorage:WaitForChild("RE")
        local ClearEvent = RE:FindFirstChild("1Clea1rTool1s")
        local ToolEvent = RE:FindFirstChild("1Too1l")
        local FireEvent = RE:FindFirstChild("1Gu1n")

        local function clearAllTools()
            if ClearEvent then
                ClearEvent:FireServer("ClearAllTools")
            end
        end
        local function getAssault()
            if ToolEvent then
                ToolEvent:InvokeServer("PickingTools", "Assault")
            end
        end
        local function hasAssault()
            return LocalPlayer.Backpack:FindFirstChild("Assault") ~= nil
        end
        local function fireAtPart(targetPart)
            local gunScript = LocalPlayer.Backpack:FindFirstChild("Assault")
                and LocalPlayer.Backpack.Assault:FindFirstChild("GunScript_Local")
            if not gunScript or not targetPart then return end
            local args = {
                targetPart,
                targetPart,
                Vector3.new(9e16, 9e16, 9e16),
                targetPart.Position,
                gunScript:FindFirstChild("MuzzleEffect"),
                gunScript:FindFirstChild("HitEffect"),
                0,
                0,
                { false },
                {
                    25,
                    Vector3.new(1000, 1000, 1000),
                    BrickColor.new(29),
                    0.25,
                    Enum.Material.SmoothPlastic,
                    0.25
                },
                true,
                false
            }
            FireEvent:FireServer(unpack(args))
        end
        local function fireAtAllPlayers(times)
            for i = 1, times do
                for _, player in ipairs(Players:GetPlayers()) do
                    if player ~= LocalPlayer and player.Character and player.Character:FindFirstChild("HumanoidRootPart") then
                        fireAtPart(player.Character.HumanoidRootPart)
                        task.wait(0.1)
                    end
                end
            end
        end
        task.spawn(function()
            while true do
                clearAllTools()
                getAssault()
                repeat
                    task.wait(0.2)
                until hasAssault()
                fireAtAllPlayers(3)
                task.wait(1)
            end
        end)
    end
})
Tab6:AddButton({
    Name = "JerkOff",
    Callback = function()
        loadstring(game:HttpGet("https://github.com/cxnker/v/raw/main/main/jerk"))()
	end
})
Tab6:AddButton({
    Name = "BringParts",
    Callback = function()
        loadstring(game:HttpGet("https://github.com/cxnker/v/raw/main/main/bringparts"))()
	end
})
Tab6:AddButton({
    Name = "Telekinesis",
    Callback = function()
        loadstring(game:HttpGet("https://github.com/cxnker/v/raw/main/main/telekinesis"))()
	end
})

Tab6:AddSection({"》 Troll Music Server"})

local audios = {
    {Name = "Gemido ultra rápido", ID = 128863565301778},
    {Name = "dodichan onnn", ID = 134640594695384},
    {Name = "amongus", ID = 6651571134},
    {Name = "Sus", ID = 6701126635},
    {Name = "SUS", ID = 7153419575},
    {Name = "Sonic.Exe", ID = 2496367477},
    {Name = "Mandrake Detected", ID = 9068077052},
    {Name = "OH MY GOD", ID = 73349649774476},
    {Name = "CHINABOY", ID = 84403553163931}
}

local audioNames = {}
for _, audio in ipairs(audios) do
    table.insert(audioNames, audio.Name)
end

Tab6:AddDropdown({
    Name = "Select audio",
    Options = audioNames,
    Default = audioNames[1],
    Callback = function(value)
        for _, audio in ipairs(audios) do
            if audio.Name == value then
                audioID = audio.ID
                break
            end
        end
    end
})

local function fireServer(eventName, args)
    local event = ReplicatedStorage:FindFirstChild("RE") and ReplicatedStorage.RE:FindFirstChild(eventName)
    if event then
        pcall(function()
            event:FireServer(unpack(args))
        end)
    end
end

local audioLoop = false

local function loopAudio()
    while audioLoop do
        if audioID then
			local args = { Workspace, audioID, 1 }
            ReplicatedStorage.RE:FindFirstChild("1Gu1nSound1s"):FireServer(unpack(args))
            local sound = Instance.new("Sound", Workspace)
            sound.SoundId = "rbxassetid://" .. audioID
            sound:Play()
        end
        task.wait(1)
    end
end

local function playAudio()
    local args = { Workspace, audioID, 1 }
		ReplicatedStorage.RE:FindFirstChild("1Gu1nSound1s"):FireServer(unpack(args))
        local sound = Instance.new("Sound", Workspace)
        sound.SoundId = "rbxassetid://" .. audioID
        sound:Play()
        task.wait(3)
        sound:Destroy()
end

Tab6:AddButton({
    Name = "Play audio",
    Callback = function()
	    if audioID then
    	    playAudio(audioID)
    	end
    end
})

Tab6:AddToggle({
    Name = "Loop audio",
    Default = false,
    Callback = function(value)
        audioLoop = value
        if audioLoop then
            task.spawn(loopAudio)
        end
    end
})
--------------------------------------------------
			-- === Tab 7: Scripts === --
--------------------------------------------------
Tab7:AddButton({
    Name = "Rejoin server",
    Callback = function()
		loadstring(game:HttpGet("https://github.com/cxnker/v/raw/main/main/rejoin"))()
    	StarterGui:SetCore("SendNotification", {
        	Title = success and "Success" or "Failed",
        	Text = success and "Rejoined now" or "Rejoin failed",
        	Duration = 5
    	})
    end
})
Tab7:AddButton({
    Name = "BoostFPS",
    Callback = function()
        loadstring(game:HttpGet("https://github.com/cxnker/v/raw/main/main/boostfps"))()
	end
})
Tab7:AddButton({
    Name = "Shaders",
    Callback = function()
        loadstring(game:HttpGet("https://github.com/cxnker/v/raw/main/main/shaders"))()
	end
})
Tab7:AddButton({
    Name = "ShiftLock",
    Callback = function()
        loadstring(game:HttpGet("https://github.com/cxnker/v/raw/main/main/shiftlock"))()
	end
})
Tab7:AddButton({
    Name = "Virtual Keyboard",
    Callback = function()
        loadstring(game:HttpGet("https://github.com/cxnker/v/raw/main/main/vkeyboard"))()
	end
})
Tab7:AddButton({
    Name = "VFly GUI",
    Callback = function()
        loadstring(game:HttpGet("https://github.com/cxnker/v/raw/main/main/vfly"))()
	end
})
Tab7:AddButton({
    Name = "Fly GUI",
    Callback = function()
        loadstring(game:HttpGet("https://github.com/nxvap/source/raw/main/fly"))()
	end
})
Tab7:AddButton({
    Name = "Silly Emotes",
    Callback = function()
		loadstring(game:HttpGet("https://github.com/Gazer-Ha/Gaze-stuff/raw/main/Silly%20emote"))()
	end
})
Tab7:AddButton({
    Name = "AFEM Emotes/Animations",
    Callback = function()
		loadstring(game:HttpGet("https://yarhm.mhi.im/scr?channel=afemmax"))()
	end
})
Tab7:AddButton({
    Name = "7yd7 Emotes/Animations",
    Callback = function()
		loadstring(game:HttpGet("https://raw.githubusercontent.com/7yd7/Hub/refs/heads/Branch/GUIS/Emotes.lua"))()
	end
})
--------------------------------------------------
			-- === Tab 8: Teleportes === --
--------------------------------------------------
Tab8:AddSection({"》 Brookhaven Sites"})

local sites = {
    {"Hill", CFrame.new(-348.64, 65.94, -458.08)},
    {"Start", CFrame.new(-26.17, 3.48, -0.93)},
    {"Hotel", CFrame.new(159.10, 3.32, 164.97)},
    {"Beach", CFrame.new(55.69, 2.94, -1403.60)},
    {"Beach2", CFrame.new(42.39, 2.94, 1336.14)},
    {"Farm", CFrame.new(-766.41, 2.92, -61.10)}
}
for _, tp in ipairs(sites) do
    Tab8:AddButton({
        tp[1],
        function()
            RootPart.CFrame = tp[2]
        end
    })
end

---------------------------------------------------

local function getPlayerNames()
    local playerNames = {}
    for _, player in ipairs(Players:GetPlayers()) do
        if player ~= LocalPlayer then
            table.insert(playerNames, player.Name)
        end
    end
    return playerNames
end

local function updateDropdown(dropdown, spectateToggle)
    pcall(function()
        local currentValue = dropdown:Get()
        local playerNames = getPlayerNames()
        dropdown:Set(playerNames) -- Mantiene el nombre del jugador
        if currentValue and not table.find(playerNames, currentValue) then
            dropdown:Set("")
            selectedPlayer = nil
            if isSpectating then
                stopSpectating()
                if spectateToggle then
                    pcall(function() spectateToggle:Set(false) end)
                end
            end
            if running or isFollowingKill or isFollowingPull then
                running = false
                isFollowingKill = false
                isFollowingPull = false
                if connection then connection:Disconnect() connection = nil end
                if flingConnection then flingConnection:Disconnect() flingConnection = nil end
                if flingToggle then pcall(function() flingToggle:Set(false) end) end
            end
        elseif currentValue and table.find(playerNames, currentValue) then
            dropdown:Set(currentValue)
        end
    end)
end

local function spectatePlayer(playerName)
    if characterConnection then
        characterConnection:Disconnect()
        characterConnection = nil
    end

    local targetPlayer = Players:FindFirstChild(playerName)
    if targetPlayer and targetPlayer ~= LocalPlayer then
        spectatedPlayer = targetPlayer
        isSpectating = true

        local function updateCamera()
            if not isSpectating or not spectatedPlayer then return end
            if spectatedPlayer.Character and spectatedPlayer.Character:FindFirstChild("Humanoid") then
                Workspace.CurrentCamera.CameraSubject = spectatedPlayer.Character.Humanoid
            else
                Workspace.CurrentCamera.CameraSubject = nil
            end
        end

        updateCamera()

        characterConnection = RunService.Heartbeat:Connect(function()
            if not isSpectating then
                characterConnection:Disconnect()
                characterConnection = nil
                return
            end
            pcall(updateCamera)
        end)

        spectatedPlayer.CharacterAdded:Connect(function()
            if isSpectating then updateCamera() end
        end)
    else
        isSpectating = false
        spectatedPlayer = nil
    end
end

local function stopSpectating()
    if characterConnection then
        characterConnection:Disconnect()
        characterConnection = nil
    end

    isSpectating = false
    spectatedPlayer = nil

    if LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("Humanoid") then
        Workspace.CurrentCamera.CameraSubject = LocalPlayer.Character.Humanoid
        Workspace.CurrentCamera.CameraType = Enum.CameraType.Custom
    else
        Workspace.CurrentCamera.CameraSubject = nil
        Workspace.CurrentCamera.CameraType = Enum.CameraType.Custom
    end
end

local function teleportToPlayer(playerName)
    local targetPlayer = Players:FindFirstChild(playerName)
    if targetPlayer and LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("HumanoidRootPart") and targetPlayer.Character and targetPlayer.Character:FindFirstChild("HumanoidRootPart") then
        local myHRP = LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
        local myHumanoid = LocalPlayer.Character:FindFirstChild("Humanoid")
        if not myHRP or not myHumanoid then
            print("Your character has not fully loaded to teleport")
            return
        end

        for _, part in ipairs(LocalPlayer.Character:GetDescendants()) do
            if part:IsA("BasePart") then
                part.Velocity = Vector3.zero
                part.RotVelocity = Vector3.zero
                part.Anchored = true
            end
        end

        local success, errorMessage = pcall(function()
            myHRP.CFrame = CFrame.new(targetPlayer.Character.HumanoidRootPart.Position + Vector3.new(0, 2, 0))
        end)
        if not success then
            warn("Teleportation failed: " .. tostring(errorMessage))
            return
        end

        myHumanoid.Sit = false
        myHumanoid:ChangeState(Enum.HumanoidStateType.GettingUp)

        task.wait(0.5)

        for _, part in ipairs(LocalPlayer.Character:GetDescendants()) do
            if part:IsA("BasePart") then
                part.Anchored = false
                part.Velocity = Vector3.zero
                part.RotVelocity = Vector3.zero
            end
        end

        print("Teleported to the player: " .. playerName .. " .")
    else
        print("Player not found to teleport")
    end
end

LocalPlayer.CharacterAdded:Connect(function(character)
    if isSpectating then
        stopSpectating()
        pcall(function() SpectateToggleTab10:Set(false) end)
    end
end)

local player_name_value

local DropdownPlayerTab2 = Tab8:AddDropdown({
    Name = "Select player",
    Description = "Choose a player to kill, lure, see, or throw",
    Default = "",
    Multi = false,
    Options = getPlayerNames(),
    Flag = "player list",
    Callback = function(selectedPlayerName)
        player_name_value = selectedPlayerName
        if selectedPlayerName == "" or selectedPlayerName == nil then
            selectedPlayer = nil
            if running or isFollowingKill or isFollowingPull then
                running = false
                isFollowingKill = false
                isFollowingPull = false
                if connection then connection:Disconnect() end
                if flingConnection then flingConnection:Disconnect() end
                if flingToggle then pcall(function() flingToggle:Set(false) end) end
            end
            if isSpectating then stopSpectating() end
        else
            selectedPlayer = Players:FindFirstChild(selectedPlayerName)
            if isSpectating then
                stopSpectating()
                spectatePlayer(selectedPlayerName)
            end
        end
    end
})

function UptadePlayers()
    local playerNames = {}
    for _, player in ipairs(Players:GetPlayers()) do
        if player.Name ~= LocalPlayer.Name then
            table.insert(playerNames, player.Name)
        end
    end
    DropdownPlayerTab2:Set(playerNames)
end

Tab8:AddButton({"Update list", function()
    UptadePlayers()
end})

UptadePlayers()

Tab8:AddButton({
    Title = "Teleport to the player",
    Callback = function()
        local selectedPlayerName = player_name_value
        if selectedPlayerName and selectedPlayerName ~= "" then
            local success, errorMessage = pcall(teleportToPlayer, selectedPlayerName)
            if not success then
                warn("Teleportation failed: " .. tostring(errorMessage))
            end
        else
            print("Select a player first")
        end
    end
})

local SpectateToggleTab10 = Tab8:AddToggle({
    Name = "View player",
    Default = false,
    Callback = function(state)
        if state then
            if selectedPlayer then
                pcall(spectatePlayer, selectedPlayer.Name)
            else
                SpectateToggleTab10:Set(false)
            end
        else
            pcall(stopSpectating)
        end
    end
})

Players.PlayerRemoving:Connect(function(player)
    updateDropdown(DropdownPlayerTab2, SpectateToggleTab10)
    if selectedPlayer == player then
        selectedPlayer = nil
        if isSpectating then stopSpectating() end
        if running then
            running = false
            if connection then connection:Disconnect() connection = nil end
            if flingConnection then flingConnection:Disconnect() flingConnection = nil end
            if flingToggle then flingToggle:Set(false) end
        end
        SpectateToggleTab10:Set(false)
        DropdownPlayerTab2:Set("")
    end
end)

Players.PlayerAdded:Connect(function()
    task.wait(1)
    updateDropdown(DropdownPlayerTab2, SpectateToggleTab10)
end)

updateDropdown(DropdownPlayerTab2, SpectateToggleTab10)
