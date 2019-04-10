;*** Has bad accuracy issues

__fpacosh:
;sqrt(x*x-1)*bgi(x,1)
  push hl,de
  push bc,af

  push bc
  pop hl
  ld e,a
  call __fpmul

  ld hl,$800000
  ld e,$BF
  call __fpadd
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
