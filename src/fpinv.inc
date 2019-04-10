__fpinv: ; CHECK: same(bitcast(uint32_t, pair8_24_t, { out.BC, out.A }),bitcast(uint32_t, float, 1.0/(bitcast(float, pair8_24_t, { in.BC, in.A }))) && out.DE == in.DE && out.HL == in.HL && out.IX == in.IX && out.IY == in.IY
;Input:  AUBC
;Output: AUBC
;Preserves: UHL, UDE
;Using Newton-Raphson division
;First step uses x0 = 32(1.5-D)/17 when .5<=D<=1
;Max error is 2/17, so we'll need 3 iterations for 24 bits
;Iterate:
;   x+x(1-d*x) -> x
  push ix,hl,de,bc
  ld ix,0
  add ix,sp

;First save the exponent and sign
  ld h,(ix+2)
  sla h
  adc a,a
  jq z,.inv_0
  inc a
  jq z,.inv_INF_NaN
  push af   ;carry is sign, A is exponent+1


;Now set the exponent to -1 and sign to positive.
  rrc h       ;reset the top bit in BC
  ld (ix+2),h
  ld bc,(ix)
  ld a,$3F    ;new exponent

;now AUBC is on [.5,1)
;Compute x0
  ld hl,$C00000
  ld e,a     ;1.5
  call __fpsub
  ld hl,$F0F0F1
  ld e,$BF   ;-32/17
  call __fpmul

;Now iterate three times
  call .inv_iter
  call .inv_iter
  call .inv_iter

;Now correct the sign and exponent
  ld (ix),bc
  sla (ix+2)
  add a,a
  ld d,a
  pop af
  push af
  ;need to D-A+80 is the new exponent.
  sub a,d
  cpl
  add a,$81
  ld d,a
  pop af
  ld a,d
  rra
  rr (ix+2)
  pop bc,de,hl,ix
  ret


.inv_iter:
;x+x(1-d*x) -> x
  push bc,af
  ld hl,(ix)
  ld e,$3F
  call __fpmul
  xor a,80h
  ld hl,$800000
  ld e,$3F  ;1.0
  call __fpadd
  pop de,hl
  ld e,d
  push hl,de
  call __fpmul
  pop de,hl
  jp __fpadd

.inv_0:
;set to infinity
  ld bc,0
  dec a
  rra
  pop bc,de,hl,ix
  ret

.inv_INF_NaN:
  rra
  sbc hl,hl
  sbc hl,bc
  jr z,.return_inf
  ld a,$FF
  ld bc,$C00000
.return_inf:
  pop bc,de,hl,ix
  ret
