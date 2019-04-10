__fpacos:
;sqrt(1-x*x)*bgi(x,1)
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
  call __fpsub
  call __fpsqrt

  push bc
  pop hl
  ld e,a

  pop af,bc
  push hl,de

  ld hl,$800000
  ld e,$3F
  call __fpibg

  pop de,hl
  call __fpmul

  pop de,hl
  ret
