__fpln:
  push hl,de
;Get the exponent and save for later
  ld hl,$800000
  add hl,bc
  adc a,a
  jq c,.return_NaN
  jq z,.return_neg_inf
  inc a
  jq z,.return_InfNaN
  push af     ;Save the exponent for later

;set exponent to 0
  ld a,$3F
  add hl,bc
  jp m,.noadjust_BC
  add hl,bc
  push hl
  pop bc
.noadjust_BC:

  push bc,af

  push bc
  ld d,a
  ld hl,$800000
  ld e,$3F
  call __fpamean
  pop hl

  push bc,af
  push hl
  pop bc
  ld a,d
  call __fpsqrt
  push bc
  pop hl
  ld e,a
  pop af,bc

  call __fpibg
  pop de,hl
  ld e,d
  push bc,af
  ld a,$BF
  ld bc,$800000
  call __fpadd
  pop de,hl
  ld e,d
  call __fpmul

  ld d,a
  pop af
  ;need to add (A-128)*ln(2)
  ;So (A*0xB17218-0x58B90C00)/2^24
  push bc,de    ;save our output

  ld h,a
  ld b,a
  ld d,a
  ld l,$B1
  mlt hl
  ld c,$72
  mlt bc
  ld e,$18
  mlt de
;HLDE
; BC
  ld a,c
  add a,d
  ld d,a
  ld a,b
  adc a,l
  ld l,a
  jr nc,$+3
  inc h

;HLDE is the 32-bit result
  ld a,d
  sub 12
  ld d,a
  ld bc,$58B9
  sbc.s hl,bc
  push af
  ;save sign
  jr nc,.nonegate
  ;negate HLDE
  push hl
  or a
  sbc hl,hl
  sbc hl,de
  ex (sp),hl
  ex de,hl
  sbc hl,de
  or a
  sbc hl,de
  pop de

.nonegate:
  ex de,hl

;D.EHL needs to be converted to a float
  ld a,h
  or l
  or e
  or d
  jr z,.fltd
  ld a,$86
.loop:
  dec a
  add.s hl,hl
  rl e
  rl d
  jp p,.loop
.fltd:
;A is the exponent, DEH is the mantissa
  ld l,a
  pop af
  ld a,l
  rra
  rl d
  rrc d
;ADEH is the float
  push de
  dec sp
  ld e,a
  ld a,h
  pop hl
  inc sp
  ld l,a
;EUHL is the float


  pop af,bc
  call __fpadd

  pop de,hl
  ret
.return_NaN:
  ld a,$7F
  ld bc,$C00000
  pop de,hl
  ret
.return_neg_inf:
  dec a   ;A is now 0xFF
  ld bc,$800000
  pop de,hl
  ret
.return_InfNaN:
  dec a
  rra
  pop de,hl
  ret
