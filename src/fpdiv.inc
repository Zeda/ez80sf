__fpdiv: ; CHECK: same(bitcast(float, pair8_24_t, { out.BC, out.A }), bitcast(float, pair8_24_t, { in.BC, in.A }) / bitcast(float, pair8_24_t, { in.HL, in.E })) && out.DE == in.DE && out.HL == in.HL && out.IX == in.IX && out.IY == in.IY
;Input:  AUBC= AUBC/EUHL
;Output: AUBC
;Preserves: UHL, UDE
;Computing as AUBC*(1/EUHL)
;save UHL and UDE
  push hl,de
  push bc,af,hl
  pop bc
  ld a,e
  call __fpinv
  pop de,hl
  ld e,d
  call __fpmul
;Restore
  pop de,hl
  ret
