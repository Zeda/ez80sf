__fpibg:
;Inverse of the Borchardt-Gauss Mean
;Inputs are a=AUBC, g=EUHL
;  b=a/2048
;  a=.5*(a+g)
;  c=21*a/512
;  c-=b
;  g=sqrt(a*g)
;  a=.5*(a+g)
;  g=sqrt(a*g)
;  a*=11/32
;  a+=c
;  a+=g
;  return 1.38427734375/a
.var_a = ix
.var_b = ix+4
.var_c = ix+8
.var_g = ix+12

  push ix,de,hl
  ld ix,-16
  add ix,sp
  ld sp,ix

  ld (.var_g),hl
  ld (.var_g+3),e

;  b=a/2048
  push hl
  ld d,a
  ld hl,$800000
  add hl,bc
  ccf
  sbc a,5
  ld (.var_b),hl
  ld (.var_b+3),a

;  a=.5*(a+g)
  ld a,d
  pop hl
  call __fpamean
  ld (.var_a),bc
  ld (.var_a+3),a

;  c=21*a/512
  ld hl,$280000
  ld e,$3D
  call __fpmul

;  c-=b
  ld hl,(.var_b)
  ld e,(.var_b+3)
  call __fpsub
  ld (.var_c),bc
  ld (.var_c+3),a

;  g=sqrt(a*g)
  ld e,(.var_a+3)
  ld hl,(.var_a)
  ld a,(.var_g+3)
  ld bc,(.var_g)
  call __fpgeomean
  ld (.var_g),bc
  ld (.var_g+3),a

;  a=.5*(a+g)
  call __fpamean
  ld (.var_a),bc
  ld (.var_a+3),a
  push bc
  pop hl
  ld e,a

;  g=sqrt(a*g)
  ld a,(.var_g+3)
  ld bc,(.var_g)
  call __fpgeomean
  ld (.var_g),bc
  ld (.var_g+3),a

;  a*=11/32
  ld bc,$B00000
  ld a,$3E
  call __fpmul

;  a+=c
  ld hl,(.var_c)
  ld e,(.var_c+3)
  call __fpadd

;  a+=g
  ld hl,(.var_g)
  ld e,(.var_g+3)
  call __fpadd


;  return 1.38427734375/a
  push bc
  pop hl
  ld e,a
  ld bc,$B13000
  ld a,$3F
  call __fpdiv

  lea hl,ix+16
  ld sp,hl
  pop hl,de,ix
  ret
