__fpasinh:
;return x/bgc((1+x*x)**.5,1.0)
  push hl,de
  push bc,af

  push bc
  pop hl
  ld e,a
  call __fpmul

  push bc
  pop hl
  ld e,a
  ld bc,$800000
  ld a,$3F
  call __fpadd
  call __fpsqrt

  ld hl,$800000
  ld e,$3F
  call __fpibg

  pop de,hl
  ld e,d
  call __fpmul

  pop de,hl
  ret
