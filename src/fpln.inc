__fpln:
  push hl,de
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
  pop de,hl
  ret
