__fpsqrt:
;AUBC = sqrt(AUBC)
;Using Newton's method
  push hl,de
  dec sp
  push bc
  inc sp
  pop hl
  sla h
  adc a,a
  jr c,.sqrt_return_NaN
  jr z,.sqrt_0
  inc a
  jr z,.sqrt_INF_NaN

;now keep the input safe
  dec a
  rra
  push af

;Make first guess
  add a,63
  rra
  push bc
  pop hl
  ld e,a
  pop af
  call .sqrt_iter
  call .sqrt_iter
  call .sqrt_iter
  call .sqrt_iter
  call .sqrt_iter
  ld a,e
  push hl
  pop bc
  pop de,hl
  ret
.sqrt_iter:
  push bc,af
  push hl,de
  call __fpdiv
  pop de,hl
  call __fpadd
  ld hl,$800000
  add hl,bc
  ccf
  sbc a,0
  ld e,a
  pop af,bc
  ret

.sqrt_return_NaN:
  ld a,$7F
  ld bc,$800000
  pop de,hl
  ret
.sqrt_INF_NaN:
  dec a
.sqrt_0:
  rra
  pop de,hl
  ret
