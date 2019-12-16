# MyPCR_Firmware



			|-------s---|		--> lid heater sensor : Tl
			|-----------|
			|	25 wells	|
			|-------s---|		--> chamber sensor	: Tc = Tcc
			|	Peltier		|
			|-----------|
			|	Aluminum	|
			|-------s---|		--> heat sink sensor : Th
			| Heat Sink	|
			|-----------|
			|		FAN			|
			|-----------|
											--> Chamber Target Temperature :Tct
											--> Current Temperature : Tcc (current chamber Temperature)

I. Fan 구동 Algorithm
		Tt > Tcc : Off
		Tt < Tcc : FULL
		Tt ~= Tcc : HALF
			
II. Peltier 구동 Algorithm

		Tt > Tcc : FULL
		Tt < Tcc : dT = abs|Th - Tcc|
							 dT < 60 : Full
							 dT >= 60 : Half
							 	
	












- v3.4 release note

>현재 heat sink sensor가 peltier와 spacer 사이에 있음 (예전에는 heat sink와 space사이에 있었음) 으로 해서
>myPCR v1에서 설정해 놓은 80도 limit을 넘는 현상이 발생했다.
> 
>이번 실험 결과 방열판 온도는 만질 수 있을 정도이므로 문제가 되지 않는다.
>그러나 peltier의 온도는 약 peak 110도 까지 오르고 있다.
>
>peltier operating 온도가 80도 이므로 이 것도 문제가 될 수 있으나
>MyPCR v1에서 peltier가 고장난 경우가 거의 없으므로 그렇지 않을 것으로 판단된다.
> 
>실제로 temperature limit은 petier element의 납땜 온도와 관계 있다
>(http://www.meerstetter.ch/compendium/tec-peltier-element-design-guide).
> 
>지속적으로 peltier 표면이 80도 일 경우에는 납땜이 녹을 수 있겠으나 이번 실험과 같이 순간적으로 110도로 올랐다가
>낮아지고 할 경우에는 문제가 되지 않을 것으로 생각된다.
> 
>그러므로 peltier 납땜 온도인 138도보다 13도 낮은 125도로 limit을 변경한 firmware (v4.4)를 올려서 현재 상태로 출고하고
>향후 peltier 불량이 나올 경우 자세히 조사해서 peltier 변경을 고려해야한다.
>(ex, tetech.com VT-127-1.4-1.15-71, 약 $37)
