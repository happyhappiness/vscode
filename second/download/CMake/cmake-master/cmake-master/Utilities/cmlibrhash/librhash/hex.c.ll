; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/hex.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@rhash_byte_to_base64.tail = internal global i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str, i32 0, i32 0), align 8
@.str = private unnamed_addr constant [13 x i8] c"0123456789+/\00", align 1
@.str.1 = private unnamed_addr constant [10 x i8] c"$-_.!'(),\00", align 1

; Function Attrs: nounwind uwtable
define i8* @rhash_print_hex_byte(i8* %dest, i8 zeroext %byte, i32 %upper_case) #0 !dbg !25 {
entry:
  %dest.addr = alloca i8*, align 8
  %byte.addr = alloca i8, align 1
  %upper_case.addr = alloca i32, align 4
  %add = alloca i8, align 1
  %c = alloca i8, align 1
  store i8* %dest, i8** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dest.addr, metadata !56, metadata !57), !dbg !58
  store i8 %byte, i8* %byte.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %byte.addr, metadata !59, metadata !57), !dbg !60
  store i32 %upper_case, i32* %upper_case.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %upper_case.addr, metadata !61, metadata !57), !dbg !62
  call void @llvm.dbg.declare(metadata i8* %add, metadata !63, metadata !57), !dbg !64
  %0 = load i32, i32* %upper_case.addr, align 4, !dbg !65
  %tobool = icmp ne i32 %0, 0, !dbg !65
  %cond = select i1 %tobool, i32 55, i32 87, !dbg !65
  %conv = trunc i32 %cond to i8, !dbg !66
  store i8 %conv, i8* %add, align 1, !dbg !64
  call void @llvm.dbg.declare(metadata i8* %c, metadata !67, metadata !57), !dbg !68
  %1 = load i8, i8* %byte.addr, align 1, !dbg !69
  %conv1 = zext i8 %1 to i32, !dbg !69
  %shr = ashr i32 %conv1, 4, !dbg !70
  %and = and i32 %shr, 15, !dbg !71
  %conv2 = trunc i32 %and to i8, !dbg !72
  store i8 %conv2, i8* %c, align 1, !dbg !68
  %2 = load i8, i8* %c, align 1, !dbg !73
  %conv3 = zext i8 %2 to i32, !dbg !73
  %cmp = icmp sgt i32 %conv3, 9, !dbg !74
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !73

cond.true:                                        ; preds = %entry
  %3 = load i8, i8* %c, align 1, !dbg !75
  %conv5 = zext i8 %3 to i32, !dbg !75
  %4 = load i8, i8* %add, align 1, !dbg !77
  %conv6 = sext i8 %4 to i32, !dbg !77
  %add7 = add nsw i32 %conv5, %conv6, !dbg !78
  br label %cond.end, !dbg !79

cond.false:                                       ; preds = %entry
  %5 = load i8, i8* %c, align 1, !dbg !80
  %conv8 = zext i8 %5 to i32, !dbg !80
  %add9 = add nsw i32 %conv8, 48, !dbg !82
  br label %cond.end, !dbg !83

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond10 = phi i32 [ %add7, %cond.true ], [ %add9, %cond.false ], !dbg !84
  %conv11 = trunc i32 %cond10 to i8, !dbg !86
  %6 = load i8*, i8** %dest.addr, align 8, !dbg !87
  %incdec.ptr = getelementptr inbounds i8, i8* %6, i32 1, !dbg !87
  store i8* %incdec.ptr, i8** %dest.addr, align 8, !dbg !87
  store i8 %conv11, i8* %6, align 1, !dbg !88
  %7 = load i8, i8* %byte.addr, align 1, !dbg !89
  %conv12 = zext i8 %7 to i32, !dbg !89
  %and13 = and i32 %conv12, 15, !dbg !90
  %conv14 = trunc i32 %and13 to i8, !dbg !89
  store i8 %conv14, i8* %c, align 1, !dbg !91
  %8 = load i8, i8* %c, align 1, !dbg !92
  %conv15 = zext i8 %8 to i32, !dbg !92
  %cmp16 = icmp sgt i32 %conv15, 9, !dbg !93
  br i1 %cmp16, label %cond.true18, label %cond.false22, !dbg !92

cond.true18:                                      ; preds = %cond.end
  %9 = load i8, i8* %c, align 1, !dbg !94
  %conv19 = zext i8 %9 to i32, !dbg !94
  %10 = load i8, i8* %add, align 1, !dbg !95
  %conv20 = sext i8 %10 to i32, !dbg !95
  %add21 = add nsw i32 %conv19, %conv20, !dbg !96
  br label %cond.end25, !dbg !97

cond.false22:                                     ; preds = %cond.end
  %11 = load i8, i8* %c, align 1, !dbg !98
  %conv23 = zext i8 %11 to i32, !dbg !98
  %add24 = add nsw i32 %conv23, 48, !dbg !99
  br label %cond.end25, !dbg !100

cond.end25:                                       ; preds = %cond.false22, %cond.true18
  %cond26 = phi i32 [ %add21, %cond.true18 ], [ %add24, %cond.false22 ], !dbg !101
  %conv27 = trunc i32 %cond26 to i8, !dbg !102
  %12 = load i8*, i8** %dest.addr, align 8, !dbg !103
  %incdec.ptr28 = getelementptr inbounds i8, i8* %12, i32 1, !dbg !103
  store i8* %incdec.ptr28, i8** %dest.addr, align 8, !dbg !103
  store i8 %conv27, i8* %12, align 1, !dbg !104
  %13 = load i8*, i8** %dest.addr, align 8, !dbg !105
  ret i8* %13, !dbg !106
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define void @rhash_byte_to_hex(i8* %dest, i8* %src, i32 %len, i32 %upper_case) #0 !dbg !31 {
entry:
  %dest.addr = alloca i8*, align 8
  %src.addr = alloca i8*, align 8
  %len.addr = alloca i32, align 4
  %upper_case.addr = alloca i32, align 4
  store i8* %dest, i8** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dest.addr, metadata !107, metadata !57), !dbg !108
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !109, metadata !57), !dbg !110
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !111, metadata !57), !dbg !112
  store i32 %upper_case, i32* %upper_case.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %upper_case.addr, metadata !113, metadata !57), !dbg !114
  br label %while.cond, !dbg !115

while.cond:                                       ; preds = %while.body, %entry
  %0 = load i32, i32* %len.addr, align 4, !dbg !116
  %dec = add i32 %0, -1, !dbg !116
  store i32 %dec, i32* %len.addr, align 4, !dbg !116
  %cmp = icmp ugt i32 %0, 0, !dbg !118
  br i1 %cmp, label %while.body, label %while.end, !dbg !119

while.body:                                       ; preds = %while.cond
  %1 = load i8*, i8** %dest.addr, align 8, !dbg !120
  %2 = load i8*, i8** %src.addr, align 8, !dbg !122
  %incdec.ptr = getelementptr inbounds i8, i8* %2, i32 1, !dbg !122
  store i8* %incdec.ptr, i8** %src.addr, align 8, !dbg !122
  %3 = load i8, i8* %2, align 1, !dbg !123
  %4 = load i32, i32* %upper_case.addr, align 4, !dbg !124
  %call = call i8* @rhash_print_hex_byte(i8* %1, i8 zeroext %3, i32 %4), !dbg !125
  store i8* %call, i8** %dest.addr, align 8, !dbg !126
  br label %while.cond, !dbg !127

while.end:                                        ; preds = %while.cond
  %5 = load i8*, i8** %dest.addr, align 8, !dbg !129
  store i8 0, i8* %5, align 1, !dbg !130
  ret void, !dbg !131
}

; Function Attrs: nounwind uwtable
define void @rhash_byte_to_base32(i8* %dest, i8* %src, i32 %len, i32 %upper_case) #0 !dbg !36 {
entry:
  %dest.addr = alloca i8*, align 8
  %src.addr = alloca i8*, align 8
  %len.addr = alloca i32, align 4
  %upper_case.addr = alloca i32, align 4
  %a = alloca i8, align 1
  %shift = alloca i32, align 4
  %word = alloca i8, align 1
  %e = alloca i8*, align 8
  store i8* %dest, i8** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dest.addr, metadata !132, metadata !57), !dbg !133
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !134, metadata !57), !dbg !135
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !136, metadata !57), !dbg !137
  store i32 %upper_case, i32* %upper_case.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %upper_case.addr, metadata !138, metadata !57), !dbg !139
  call void @llvm.dbg.declare(metadata i8* %a, metadata !140, metadata !57), !dbg !141
  %0 = load i32, i32* %upper_case.addr, align 4, !dbg !142
  %tobool = icmp ne i32 %0, 0, !dbg !142
  %cond = select i1 %tobool, i32 65, i32 97, !dbg !142
  %conv = trunc i32 %cond to i8, !dbg !143
  store i8 %conv, i8* %a, align 1, !dbg !141
  call void @llvm.dbg.declare(metadata i32* %shift, metadata !144, metadata !57), !dbg !145
  store i32 0, i32* %shift, align 4, !dbg !145
  call void @llvm.dbg.declare(metadata i8* %word, metadata !146, metadata !57), !dbg !147
  call void @llvm.dbg.declare(metadata i8** %e, metadata !148, metadata !57), !dbg !149
  %1 = load i8*, i8** %src.addr, align 8, !dbg !150
  %2 = load i32, i32* %len.addr, align 4, !dbg !151
  %idx.ext = zext i32 %2 to i64, !dbg !152
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 %idx.ext, !dbg !152
  store i8* %add.ptr, i8** %e, align 8, !dbg !149
  br label %while.cond, !dbg !153

while.cond:                                       ; preds = %cond.end, %entry
  %3 = load i8*, i8** %src.addr, align 8, !dbg !154
  %4 = load i8*, i8** %e, align 8, !dbg !156
  %cmp = icmp ult i8* %3, %4, !dbg !157
  br i1 %cmp, label %while.body, label %while.end, !dbg !158

while.body:                                       ; preds = %while.cond
  %5 = load i32, i32* %shift, align 4, !dbg !159
  %cmp2 = icmp ugt i32 %5, 3, !dbg !162
  br i1 %cmp2, label %if.then, label %if.else, !dbg !163

if.then:                                          ; preds = %while.body
  %6 = load i8*, i8** %src.addr, align 8, !dbg !164
  %7 = load i8, i8* %6, align 1, !dbg !166
  %conv4 = zext i8 %7 to i32, !dbg !166
  %8 = load i32, i32* %shift, align 4, !dbg !167
  %shr = ashr i32 255, %8, !dbg !168
  %and = and i32 %conv4, %shr, !dbg !169
  %conv5 = trunc i32 %and to i8, !dbg !170
  store i8 %conv5, i8* %word, align 1, !dbg !171
  %9 = load i32, i32* %shift, align 4, !dbg !172
  %add = add i32 %9, 5, !dbg !173
  %rem = urem i32 %add, 8, !dbg !174
  store i32 %rem, i32* %shift, align 4, !dbg !175
  %10 = load i32, i32* %shift, align 4, !dbg !176
  %11 = load i8, i8* %word, align 1, !dbg !177
  %conv6 = zext i8 %11 to i32, !dbg !177
  %shl = shl i32 %conv6, %10, !dbg !177
  %conv7 = trunc i32 %shl to i8, !dbg !177
  store i8 %conv7, i8* %word, align 1, !dbg !177
  %12 = load i8*, i8** %src.addr, align 8, !dbg !178
  %add.ptr8 = getelementptr inbounds i8, i8* %12, i64 1, !dbg !180
  %13 = load i8*, i8** %e, align 8, !dbg !181
  %cmp9 = icmp ult i8* %add.ptr8, %13, !dbg !182
  br i1 %cmp9, label %if.then11, label %if.end, !dbg !183

if.then11:                                        ; preds = %if.then
  %14 = load i8*, i8** %src.addr, align 8, !dbg !184
  %add.ptr12 = getelementptr inbounds i8, i8* %14, i64 1, !dbg !185
  %15 = load i8, i8* %add.ptr12, align 1, !dbg !186
  %conv13 = zext i8 %15 to i32, !dbg !186
  %16 = load i32, i32* %shift, align 4, !dbg !187
  %sub = sub i32 8, %16, !dbg !188
  %shr14 = ashr i32 %conv13, %sub, !dbg !189
  %17 = load i8, i8* %word, align 1, !dbg !190
  %conv15 = zext i8 %17 to i32, !dbg !190
  %or = or i32 %conv15, %shr14, !dbg !190
  %conv16 = trunc i32 %or to i8, !dbg !190
  store i8 %conv16, i8* %word, align 1, !dbg !190
  br label %if.end, !dbg !191

if.end:                                           ; preds = %if.then11, %if.then
  %18 = load i8*, i8** %src.addr, align 8, !dbg !192
  %incdec.ptr = getelementptr inbounds i8, i8* %18, i32 1, !dbg !192
  store i8* %incdec.ptr, i8** %src.addr, align 8, !dbg !192
  br label %if.end30, !dbg !193

if.else:                                          ; preds = %while.body
  %19 = load i32, i32* %shift, align 4, !dbg !194
  %add17 = add i32 %19, 5, !dbg !196
  %rem18 = urem i32 %add17, 8, !dbg !197
  store i32 %rem18, i32* %shift, align 4, !dbg !198
  %20 = load i8*, i8** %src.addr, align 8, !dbg !199
  %21 = load i8, i8* %20, align 1, !dbg !200
  %conv19 = zext i8 %21 to i32, !dbg !200
  %22 = load i32, i32* %shift, align 4, !dbg !201
  %sub20 = sub i32 8, %22, !dbg !202
  %and21 = and i32 %sub20, 7, !dbg !203
  %shr22 = ashr i32 %conv19, %and21, !dbg !204
  %and23 = and i32 %shr22, 31, !dbg !205
  %conv24 = trunc i32 %and23 to i8, !dbg !206
  store i8 %conv24, i8* %word, align 1, !dbg !207
  %23 = load i32, i32* %shift, align 4, !dbg !208
  %cmp25 = icmp eq i32 %23, 0, !dbg !210
  br i1 %cmp25, label %if.then27, label %if.end29, !dbg !211

if.then27:                                        ; preds = %if.else
  %24 = load i8*, i8** %src.addr, align 8, !dbg !212
  %incdec.ptr28 = getelementptr inbounds i8, i8* %24, i32 1, !dbg !212
  store i8* %incdec.ptr28, i8** %src.addr, align 8, !dbg !212
  br label %if.end29, !dbg !214

if.end29:                                         ; preds = %if.then27, %if.else
  br label %if.end30

if.end30:                                         ; preds = %if.end29, %if.end
  %25 = load i8, i8* %word, align 1, !dbg !215
  %conv31 = zext i8 %25 to i32, !dbg !215
  %cmp32 = icmp slt i32 %conv31, 26, !dbg !216
  br i1 %cmp32, label %cond.true, label %cond.false, !dbg !215

cond.true:                                        ; preds = %if.end30
  %26 = load i8, i8* %word, align 1, !dbg !217
  %conv34 = zext i8 %26 to i32, !dbg !217
  %27 = load i8, i8* %a, align 1, !dbg !219
  %conv35 = sext i8 %27 to i32, !dbg !219
  %add36 = add nsw i32 %conv34, %conv35, !dbg !220
  br label %cond.end, !dbg !221

cond.false:                                       ; preds = %if.end30
  %28 = load i8, i8* %word, align 1, !dbg !222
  %conv37 = zext i8 %28 to i32, !dbg !222
  %add38 = add nsw i32 %conv37, 50, !dbg !224
  %sub39 = sub nsw i32 %add38, 26, !dbg !225
  br label %cond.end, !dbg !226

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond40 = phi i32 [ %add36, %cond.true ], [ %sub39, %cond.false ], !dbg !227
  %conv41 = trunc i32 %cond40 to i8, !dbg !229
  %29 = load i8*, i8** %dest.addr, align 8, !dbg !230
  %incdec.ptr42 = getelementptr inbounds i8, i8* %29, i32 1, !dbg !230
  store i8* %incdec.ptr42, i8** %dest.addr, align 8, !dbg !230
  store i8 %conv41, i8* %29, align 1, !dbg !231
  br label %while.cond, !dbg !232

while.end:                                        ; preds = %while.cond
  %30 = load i8*, i8** %dest.addr, align 8, !dbg !234
  store i8 0, i8* %30, align 1, !dbg !235
  ret void, !dbg !236
}

; Function Attrs: nounwind uwtable
define void @rhash_byte_to_base64(i8* %dest, i8* %src, i32 %len) #0 !dbg !37 {
entry:
  %dest.addr = alloca i8*, align 8
  %src.addr = alloca i8*, align 8
  %len.addr = alloca i32, align 4
  %shift = alloca i32, align 4
  %word = alloca i8, align 1
  %e = alloca i8*, align 8
  store i8* %dest, i8** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dest.addr, metadata !237, metadata !57), !dbg !238
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !239, metadata !57), !dbg !240
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !241, metadata !57), !dbg !242
  call void @llvm.dbg.declare(metadata i32* %shift, metadata !243, metadata !57), !dbg !244
  store i32 0, i32* %shift, align 4, !dbg !244
  call void @llvm.dbg.declare(metadata i8* %word, metadata !245, metadata !57), !dbg !246
  call void @llvm.dbg.declare(metadata i8** %e, metadata !247, metadata !57), !dbg !248
  %0 = load i8*, i8** %src.addr, align 8, !dbg !249
  %1 = load i32, i32* %len.addr, align 4, !dbg !250
  %idx.ext = zext i32 %1 to i64, !dbg !251
  %add.ptr = getelementptr inbounds i8, i8* %0, i64 %idx.ext, !dbg !251
  store i8* %add.ptr, i8** %e, align 8, !dbg !248
  br label %while.cond, !dbg !252

while.cond:                                       ; preds = %cond.end44, %entry
  %2 = load i8*, i8** %src.addr, align 8, !dbg !253
  %3 = load i8*, i8** %e, align 8, !dbg !255
  %cmp = icmp ult i8* %2, %3, !dbg !256
  br i1 %cmp, label %while.body, label %while.end, !dbg !257

while.body:                                       ; preds = %while.cond
  %4 = load i32, i32* %shift, align 4, !dbg !258
  %cmp1 = icmp ugt i32 %4, 2, !dbg !261
  br i1 %cmp1, label %if.then, label %if.else, !dbg !262

if.then:                                          ; preds = %while.body
  %5 = load i8*, i8** %src.addr, align 8, !dbg !263
  %6 = load i8, i8* %5, align 1, !dbg !265
  %conv = zext i8 %6 to i32, !dbg !265
  %7 = load i32, i32* %shift, align 4, !dbg !266
  %shr = ashr i32 255, %7, !dbg !267
  %and = and i32 %conv, %shr, !dbg !268
  %conv2 = trunc i32 %and to i8, !dbg !269
  store i8 %conv2, i8* %word, align 1, !dbg !270
  %8 = load i32, i32* %shift, align 4, !dbg !271
  %add = add i32 %8, 6, !dbg !272
  %rem = urem i32 %add, 8, !dbg !273
  store i32 %rem, i32* %shift, align 4, !dbg !274
  %9 = load i32, i32* %shift, align 4, !dbg !275
  %10 = load i8, i8* %word, align 1, !dbg !276
  %conv3 = zext i8 %10 to i32, !dbg !276
  %shl = shl i32 %conv3, %9, !dbg !276
  %conv4 = trunc i32 %shl to i8, !dbg !276
  store i8 %conv4, i8* %word, align 1, !dbg !276
  %11 = load i8*, i8** %src.addr, align 8, !dbg !277
  %add.ptr5 = getelementptr inbounds i8, i8* %11, i64 1, !dbg !279
  %12 = load i8*, i8** %e, align 8, !dbg !280
  %cmp6 = icmp ult i8* %add.ptr5, %12, !dbg !281
  br i1 %cmp6, label %if.then8, label %if.end, !dbg !282

if.then8:                                         ; preds = %if.then
  %13 = load i8*, i8** %src.addr, align 8, !dbg !283
  %add.ptr9 = getelementptr inbounds i8, i8* %13, i64 1, !dbg !284
  %14 = load i8, i8* %add.ptr9, align 1, !dbg !285
  %conv10 = zext i8 %14 to i32, !dbg !285
  %15 = load i32, i32* %shift, align 4, !dbg !286
  %sub = sub i32 8, %15, !dbg !287
  %shr11 = ashr i32 %conv10, %sub, !dbg !288
  %16 = load i8, i8* %word, align 1, !dbg !289
  %conv12 = zext i8 %16 to i32, !dbg !289
  %or = or i32 %conv12, %shr11, !dbg !289
  %conv13 = trunc i32 %or to i8, !dbg !289
  store i8 %conv13, i8* %word, align 1, !dbg !289
  br label %if.end, !dbg !290

if.end:                                           ; preds = %if.then8, %if.then
  %17 = load i8*, i8** %src.addr, align 8, !dbg !291
  %incdec.ptr = getelementptr inbounds i8, i8* %17, i32 1, !dbg !291
  store i8* %incdec.ptr, i8** %src.addr, align 8, !dbg !291
  br label %if.end27, !dbg !292

if.else:                                          ; preds = %while.body
  %18 = load i32, i32* %shift, align 4, !dbg !293
  %add14 = add i32 %18, 6, !dbg !295
  %rem15 = urem i32 %add14, 8, !dbg !296
  store i32 %rem15, i32* %shift, align 4, !dbg !297
  %19 = load i8*, i8** %src.addr, align 8, !dbg !298
  %20 = load i8, i8* %19, align 1, !dbg !299
  %conv16 = zext i8 %20 to i32, !dbg !299
  %21 = load i32, i32* %shift, align 4, !dbg !300
  %sub17 = sub i32 8, %21, !dbg !301
  %and18 = and i32 %sub17, 7, !dbg !302
  %shr19 = ashr i32 %conv16, %and18, !dbg !303
  %and20 = and i32 %shr19, 63, !dbg !304
  %conv21 = trunc i32 %and20 to i8, !dbg !305
  store i8 %conv21, i8* %word, align 1, !dbg !306
  %22 = load i32, i32* %shift, align 4, !dbg !307
  %cmp22 = icmp eq i32 %22, 0, !dbg !309
  br i1 %cmp22, label %if.then24, label %if.end26, !dbg !310

if.then24:                                        ; preds = %if.else
  %23 = load i8*, i8** %src.addr, align 8, !dbg !311
  %incdec.ptr25 = getelementptr inbounds i8, i8* %23, i32 1, !dbg !311
  store i8* %incdec.ptr25, i8** %src.addr, align 8, !dbg !311
  br label %if.end26, !dbg !313

if.end26:                                         ; preds = %if.then24, %if.else
  br label %if.end27

if.end27:                                         ; preds = %if.end26, %if.end
  %24 = load i8, i8* %word, align 1, !dbg !314
  %conv28 = zext i8 %24 to i32, !dbg !314
  %cmp29 = icmp slt i32 %conv28, 52, !dbg !315
  br i1 %cmp29, label %cond.true, label %cond.false40, !dbg !314

cond.true:                                        ; preds = %if.end27
  %25 = load i8, i8* %word, align 1, !dbg !316
  %conv31 = zext i8 %25 to i32, !dbg !316
  %cmp32 = icmp slt i32 %conv31, 26, !dbg !318
  br i1 %cmp32, label %cond.true34, label %cond.false, !dbg !316

cond.true34:                                      ; preds = %cond.true
  %26 = load i8, i8* %word, align 1, !dbg !319
  %conv35 = zext i8 %26 to i32, !dbg !319
  %add36 = add nsw i32 %conv35, 65, !dbg !321
  br label %cond.end, !dbg !322

cond.false:                                       ; preds = %cond.true
  %27 = load i8, i8* %word, align 1, !dbg !323
  %conv37 = zext i8 %27 to i32, !dbg !323
  %sub38 = sub nsw i32 %conv37, 26, !dbg !325
  %add39 = add nsw i32 %sub38, 97, !dbg !326
  br label %cond.end, !dbg !327

cond.end:                                         ; preds = %cond.false, %cond.true34
  %cond = phi i32 [ %add36, %cond.true34 ], [ %add39, %cond.false ], !dbg !328
  br label %cond.end44, !dbg !330

cond.false40:                                     ; preds = %if.end27
  %28 = load i8, i8* %word, align 1, !dbg !331
  %conv41 = zext i8 %28 to i32, !dbg !331
  %sub42 = sub nsw i32 %conv41, 52, !dbg !333
  %idxprom = sext i32 %sub42 to i64, !dbg !334
  %29 = load i8*, i8** @rhash_byte_to_base64.tail, align 8, !dbg !334
  %arrayidx = getelementptr inbounds i8, i8* %29, i64 %idxprom, !dbg !334
  %30 = load i8, i8* %arrayidx, align 1, !dbg !334
  %conv43 = sext i8 %30 to i32, !dbg !334
  br label %cond.end44, !dbg !335

cond.end44:                                       ; preds = %cond.false40, %cond.end
  %cond45 = phi i32 [ %cond, %cond.end ], [ %conv43, %cond.false40 ], !dbg !336
  %conv46 = trunc i32 %cond45 to i8, !dbg !338
  %31 = load i8*, i8** %dest.addr, align 8, !dbg !339
  %incdec.ptr47 = getelementptr inbounds i8, i8* %31, i32 1, !dbg !339
  store i8* %incdec.ptr47, i8** %dest.addr, align 8, !dbg !339
  store i8 %conv46, i8* %31, align 1, !dbg !340
  br label %while.cond, !dbg !341

while.end:                                        ; preds = %while.cond
  %32 = load i32, i32* %shift, align 4, !dbg !343
  %cmp48 = icmp ugt i32 %32, 0, !dbg !345
  br i1 %cmp48, label %if.then50, label %if.end57, !dbg !346

if.then50:                                        ; preds = %while.end
  %33 = load i8*, i8** %dest.addr, align 8, !dbg !347
  %incdec.ptr51 = getelementptr inbounds i8, i8* %33, i32 1, !dbg !347
  store i8* %incdec.ptr51, i8** %dest.addr, align 8, !dbg !347
  store i8 61, i8* %33, align 1, !dbg !349
  %34 = load i32, i32* %shift, align 4, !dbg !350
  %cmp52 = icmp eq i32 %34, 4, !dbg !352
  br i1 %cmp52, label %if.then54, label %if.end56, !dbg !353

if.then54:                                        ; preds = %if.then50
  %35 = load i8*, i8** %dest.addr, align 8, !dbg !354
  %incdec.ptr55 = getelementptr inbounds i8, i8* %35, i32 1, !dbg !354
  store i8* %incdec.ptr55, i8** %dest.addr, align 8, !dbg !354
  store i8 61, i8* %35, align 1, !dbg !356
  br label %if.end56, !dbg !357

if.end56:                                         ; preds = %if.then54, %if.then50
  br label %if.end57, !dbg !358

if.end57:                                         ; preds = %if.end56, %while.end
  %36 = load i8*, i8** %dest.addr, align 8, !dbg !359
  store i8 0, i8* %36, align 1, !dbg !360
  ret void, !dbg !361
}

; Function Attrs: nounwind uwtable
define i32 @rhash_urlencode(i8* %dst, i8* %name) #0 !dbg !40 {
entry:
  %retval = alloca i32, align 4
  %dst.addr = alloca i8*, align 8
  %name.addr = alloca i8*, align 8
  %start = alloca i8*, align 8
  %len = alloca i32, align 4
  store i8* %dst, i8** %dst.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dst.addr, metadata !362, metadata !57), !dbg !363
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !364, metadata !57), !dbg !365
  call void @llvm.dbg.declare(metadata i8** %start, metadata !366, metadata !57), !dbg !367
  %0 = load i8*, i8** %dst.addr, align 8, !dbg !368
  %tobool = icmp ne i8* %0, null, !dbg !368
  br i1 %tobool, label %if.end, label %if.then, !dbg !370

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %len, metadata !371, metadata !57), !dbg !373
  store i32 0, i32* %len, align 4, !dbg !374
  br label %for.cond, !dbg !376

for.cond:                                         ; preds = %for.inc, %if.then
  %1 = load i8*, i8** %name.addr, align 8, !dbg !377
  %2 = load i8, i8* %1, align 1, !dbg !380
  %tobool1 = icmp ne i8 %2, 0, !dbg !381
  br i1 %tobool1, label %for.body, label %for.end, !dbg !381

for.body:                                         ; preds = %for.cond
  %3 = load i8*, i8** %name.addr, align 8, !dbg !382
  %4 = load i8, i8* %3, align 1, !dbg !382
  %conv = zext i8 %4 to i32, !dbg !382
  %idxprom = sext i32 %conv to i64, !dbg !382
  %call = call i16** @__ctype_b_loc() #1, !dbg !382
  %5 = load i16*, i16** %call, align 8, !dbg !382
  %arrayidx = getelementptr inbounds i16, i16* %5, i64 %idxprom, !dbg !382
  %6 = load i16, i16* %arrayidx, align 2, !dbg !382
  %conv2 = zext i16 %6 to i32, !dbg !382
  %and = and i32 %conv2, 8, !dbg !382
  %tobool3 = icmp ne i32 %and, 0, !dbg !382
  br i1 %tobool3, label %lor.end, label %lor.rhs, !dbg !382

lor.rhs:                                          ; preds = %for.body
  %7 = load i8*, i8** %name.addr, align 8, !dbg !384
  %8 = load i8, i8* %7, align 1, !dbg !384
  %conv4 = sext i8 %8 to i32, !dbg !384
  %call5 = call i8* @strchr(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.1, i32 0, i32 0), i32 %conv4) #5, !dbg !384
  %tobool6 = icmp ne i8* %call5, null, !dbg !384
  br label %lor.end, !dbg !384

lor.end:                                          ; preds = %lor.rhs, %for.body
  %9 = phi i1 [ true, %for.body ], [ %tobool6, %lor.rhs ]
  %cond = select i1 %9, i32 1, i32 3, !dbg !386
  %10 = load i32, i32* %len, align 4, !dbg !388
  %add = add nsw i32 %10, %cond, !dbg !388
  store i32 %add, i32* %len, align 4, !dbg !388
  br label %for.inc, !dbg !389

for.inc:                                          ; preds = %lor.end
  %11 = load i8*, i8** %name.addr, align 8, !dbg !390
  %incdec.ptr = getelementptr inbounds i8, i8* %11, i32 1, !dbg !390
  store i8* %incdec.ptr, i8** %name.addr, align 8, !dbg !390
  br label %for.cond, !dbg !392

for.end:                                          ; preds = %for.cond
  %12 = load i32, i32* %len, align 4, !dbg !393
  store i32 %12, i32* %retval, align 4, !dbg !394
  br label %return, !dbg !394

if.end:                                           ; preds = %entry
  %13 = load i8*, i8** %dst.addr, align 8, !dbg !395
  store i8* %13, i8** %start, align 8, !dbg !397
  br label %for.cond7, !dbg !398

for.cond7:                                        ; preds = %for.inc25, %if.end
  %14 = load i8*, i8** %name.addr, align 8, !dbg !399
  %15 = load i8, i8* %14, align 1, !dbg !402
  %tobool8 = icmp ne i8 %15, 0, !dbg !403
  br i1 %tobool8, label %for.body9, label %for.end27, !dbg !403

for.body9:                                        ; preds = %for.cond7
  %16 = load i8*, i8** %name.addr, align 8, !dbg !404
  %17 = load i8, i8* %16, align 1, !dbg !404
  %conv10 = zext i8 %17 to i32, !dbg !404
  %idxprom11 = sext i32 %conv10 to i64, !dbg !404
  %call12 = call i16** @__ctype_b_loc() #1, !dbg !404
  %18 = load i16*, i16** %call12, align 8, !dbg !404
  %arrayidx13 = getelementptr inbounds i16, i16* %18, i64 %idxprom11, !dbg !404
  %19 = load i16, i16* %arrayidx13, align 2, !dbg !404
  %conv14 = zext i16 %19 to i32, !dbg !404
  %and15 = and i32 %conv14, 8, !dbg !404
  %tobool16 = icmp ne i32 %and15, 0, !dbg !404
  br i1 %tobool16, label %if.then20, label %lor.lhs.false, !dbg !404

lor.lhs.false:                                    ; preds = %for.body9
  %20 = load i8*, i8** %name.addr, align 8, !dbg !407
  %21 = load i8, i8* %20, align 1, !dbg !407
  %conv17 = sext i8 %21 to i32, !dbg !407
  %call18 = call i8* @strchr(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.1, i32 0, i32 0), i32 %conv17) #5, !dbg !407
  %tobool19 = icmp ne i8* %call18, null, !dbg !407
  br i1 %tobool19, label %if.then20, label %if.else, !dbg !407

if.then20:                                        ; preds = %lor.lhs.false, %for.body9
  %22 = load i8*, i8** %name.addr, align 8, !dbg !409
  %23 = load i8, i8* %22, align 1, !dbg !411
  %24 = load i8*, i8** %dst.addr, align 8, !dbg !412
  %incdec.ptr21 = getelementptr inbounds i8, i8* %24, i32 1, !dbg !412
  store i8* %incdec.ptr21, i8** %dst.addr, align 8, !dbg !412
  store i8 %23, i8* %24, align 1, !dbg !413
  br label %if.end24, !dbg !414

if.else:                                          ; preds = %lor.lhs.false
  %25 = load i8*, i8** %dst.addr, align 8, !dbg !415
  %incdec.ptr22 = getelementptr inbounds i8, i8* %25, i32 1, !dbg !415
  store i8* %incdec.ptr22, i8** %dst.addr, align 8, !dbg !415
  store i8 37, i8* %25, align 1, !dbg !417
  %26 = load i8*, i8** %dst.addr, align 8, !dbg !418
  %27 = load i8*, i8** %name.addr, align 8, !dbg !419
  %28 = load i8, i8* %27, align 1, !dbg !420
  %call23 = call i8* @rhash_print_hex_byte(i8* %26, i8 zeroext %28, i32 65), !dbg !421
  store i8* %call23, i8** %dst.addr, align 8, !dbg !422
  br label %if.end24

if.end24:                                         ; preds = %if.else, %if.then20
  br label %for.inc25, !dbg !423

for.inc25:                                        ; preds = %if.end24
  %29 = load i8*, i8** %name.addr, align 8, !dbg !424
  %incdec.ptr26 = getelementptr inbounds i8, i8* %29, i32 1, !dbg !424
  store i8* %incdec.ptr26, i8** %name.addr, align 8, !dbg !424
  br label %for.cond7, !dbg !426

for.end27:                                        ; preds = %for.cond7
  %30 = load i8*, i8** %dst.addr, align 8, !dbg !427
  store i8 0, i8* %30, align 1, !dbg !428
  %31 = load i8*, i8** %dst.addr, align 8, !dbg !429
  %32 = load i8*, i8** %start, align 8, !dbg !430
  %sub.ptr.lhs.cast = ptrtoint i8* %31 to i64, !dbg !431
  %sub.ptr.rhs.cast = ptrtoint i8* %32 to i64, !dbg !431
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !431
  %conv28 = trunc i64 %sub.ptr.sub to i32, !dbg !432
  store i32 %conv28, i32* %retval, align 4, !dbg !433
  br label %return, !dbg !433

return:                                           ; preds = %for.end27, %for.end
  %33 = load i32, i32* %retval, align 4, !dbg !434
  ret i32 %33, !dbg !434
}

; Function Attrs: nounwind readnone
declare i16** @__ctype_b_loc() #2

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #3

; Function Attrs: nounwind uwtable
define i32 @rhash_sprintI64(i8* %dst, i64 %number) #0 !dbg !45 {
entry:
  %retval = alloca i32, align 4
  %dst.addr = alloca i8*, align 8
  %number.addr = alloca i64, align 8
  %buf = alloca [24 x i8], align 16
  %p = alloca i8*, align 8
  %length = alloca i64, align 8
  store i8* %dst, i8** %dst.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dst.addr, metadata !435, metadata !57), !dbg !436
  store i64 %number, i64* %number.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %number.addr, metadata !437, metadata !57), !dbg !438
  call void @llvm.dbg.declare(metadata [24 x i8]* %buf, metadata !439, metadata !57), !dbg !443
  call void @llvm.dbg.declare(metadata i8** %p, metadata !444, metadata !57), !dbg !445
  call void @llvm.dbg.declare(metadata i64* %length, metadata !446, metadata !57), !dbg !449
  %0 = load i8*, i8** %dst.addr, align 8, !dbg !450
  %cmp = icmp eq i8* %0, null, !dbg !452
  br i1 %cmp, label %if.then, label %if.end4, !dbg !453

if.then:                                          ; preds = %entry
  %1 = load i64, i64* %number.addr, align 8, !dbg !454
  %cmp1 = icmp eq i64 %1, 0, !dbg !457
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !458

if.then2:                                         ; preds = %if.then
  store i32 1, i32* %retval, align 4, !dbg !459
  br label %return, !dbg !459

if.end:                                           ; preds = %if.then
  store i64 0, i64* %length, align 8, !dbg !461
  br label %for.cond, !dbg !463

for.cond:                                         ; preds = %for.inc, %if.end
  %2 = load i64, i64* %number.addr, align 8, !dbg !464
  %cmp3 = icmp ne i64 %2, 0, !dbg !467
  br i1 %cmp3, label %for.body, label %for.end, !dbg !468

for.body:                                         ; preds = %for.cond
  %3 = load i64, i64* %length, align 8, !dbg !469
  %inc = add i64 %3, 1, !dbg !469
  store i64 %inc, i64* %length, align 8, !dbg !469
  br label %for.inc, !dbg !471

for.inc:                                          ; preds = %for.body
  %4 = load i64, i64* %number.addr, align 8, !dbg !472
  %div = udiv i64 %4, 10, !dbg !472
  store i64 %div, i64* %number.addr, align 8, !dbg !472
  br label %for.cond, !dbg !474

for.end:                                          ; preds = %for.cond
  %5 = load i64, i64* %length, align 8, !dbg !475
  %conv = trunc i64 %5 to i32, !dbg !476
  store i32 %conv, i32* %retval, align 4, !dbg !477
  br label %return, !dbg !477

if.end4:                                          ; preds = %entry
  %arraydecay = getelementptr inbounds [24 x i8], [24 x i8]* %buf, i32 0, i32 0, !dbg !478
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay, i64 23, !dbg !479
  store i8* %add.ptr, i8** %p, align 8, !dbg !480
  %6 = load i8*, i8** %p, align 8, !dbg !481
  store i8 0, i8* %6, align 1, !dbg !482
  %7 = load i64, i64* %number.addr, align 8, !dbg !483
  %cmp5 = icmp eq i64 %7, 0, !dbg !485
  br i1 %cmp5, label %if.then7, label %if.else, !dbg !486

if.then7:                                         ; preds = %if.end4
  %8 = load i8*, i8** %p, align 8, !dbg !487
  %incdec.ptr = getelementptr inbounds i8, i8* %8, i32 -1, !dbg !487
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !487
  store i8 48, i8* %incdec.ptr, align 1, !dbg !489
  br label %if.end22, !dbg !490

if.else:                                          ; preds = %if.end4
  br label %for.cond8, !dbg !491

for.cond8:                                        ; preds = %for.inc19, %if.else
  %9 = load i8*, i8** %p, align 8, !dbg !493
  %arraydecay9 = getelementptr inbounds [24 x i8], [24 x i8]* %buf, i32 0, i32 0, !dbg !497
  %cmp10 = icmp uge i8* %9, %arraydecay9, !dbg !498
  br i1 %cmp10, label %land.rhs, label %land.end, !dbg !499

land.rhs:                                         ; preds = %for.cond8
  %10 = load i64, i64* %number.addr, align 8, !dbg !500
  %cmp12 = icmp ne i64 %10, 0, !dbg !502
  br label %land.end

land.end:                                         ; preds = %land.rhs, %for.cond8
  %11 = phi i1 [ false, %for.cond8 ], [ %cmp12, %land.rhs ]
  br i1 %11, label %for.body14, label %for.end21, !dbg !503

for.body14:                                       ; preds = %land.end
  %12 = load i64, i64* %number.addr, align 8, !dbg !505
  %rem = urem i64 %12, 10, !dbg !507
  %conv15 = trunc i64 %rem to i8, !dbg !508
  %conv16 = sext i8 %conv15 to i32, !dbg !508
  %add = add nsw i32 48, %conv16, !dbg !509
  %conv17 = trunc i32 %add to i8, !dbg !510
  %13 = load i8*, i8** %p, align 8, !dbg !511
  %incdec.ptr18 = getelementptr inbounds i8, i8* %13, i32 -1, !dbg !511
  store i8* %incdec.ptr18, i8** %p, align 8, !dbg !511
  store i8 %conv17, i8* %incdec.ptr18, align 1, !dbg !512
  br label %for.inc19, !dbg !513

for.inc19:                                        ; preds = %for.body14
  %14 = load i64, i64* %number.addr, align 8, !dbg !514
  %div20 = udiv i64 %14, 10, !dbg !514
  store i64 %div20, i64* %number.addr, align 8, !dbg !514
  br label %for.cond8, !dbg !516

for.end21:                                        ; preds = %land.end
  br label %if.end22

if.end22:                                         ; preds = %for.end21, %if.then7
  %arraydecay23 = getelementptr inbounds [24 x i8], [24 x i8]* %buf, i32 0, i32 0, !dbg !517
  %add.ptr24 = getelementptr inbounds i8, i8* %arraydecay23, i64 23, !dbg !518
  %15 = load i8*, i8** %p, align 8, !dbg !519
  %sub.ptr.lhs.cast = ptrtoint i8* %add.ptr24 to i64, !dbg !520
  %sub.ptr.rhs.cast = ptrtoint i8* %15 to i64, !dbg !520
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !520
  store i64 %sub.ptr.sub, i64* %length, align 8, !dbg !521
  %16 = load i8*, i8** %dst.addr, align 8, !dbg !522
  %17 = load i8*, i8** %p, align 8, !dbg !523
  %18 = load i64, i64* %length, align 8, !dbg !524
  %add25 = add i64 %18, 1, !dbg !525
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %16, i8* %17, i64 %add25, i32 1, i1 false), !dbg !526
  %19 = load i64, i64* %length, align 8, !dbg !527
  %conv26 = trunc i64 %19 to i32, !dbg !528
  store i32 %conv26, i32* %retval, align 4, !dbg !529
  br label %return, !dbg !529

return:                                           ; preds = %if.end22, %for.end, %if.then2
  %20 = load i32, i32* %retval, align 4, !dbg !530
  ret i32 %20, !dbg !530
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!53, !54}
!llvm.ident = !{!55}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !18, subprograms: !24, globals: !51)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/hex.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 46, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/usr/include/ctype.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17}
!6 = !DIEnumerator(name: "_ISupper", value: 256)
!7 = !DIEnumerator(name: "_ISlower", value: 512)
!8 = !DIEnumerator(name: "_ISalpha", value: 1024)
!9 = !DIEnumerator(name: "_ISdigit", value: 2048)
!10 = !DIEnumerator(name: "_ISxdigit", value: 4096)
!11 = !DIEnumerator(name: "_ISspace", value: 8192)
!12 = !DIEnumerator(name: "_ISprint", value: 16384)
!13 = !DIEnumerator(name: "_ISgraph", value: 32768)
!14 = !DIEnumerator(name: "_ISblank", value: 1)
!15 = !DIEnumerator(name: "_IScntrl", value: 2)
!16 = !DIEnumerator(name: "_ISpunct", value: 4)
!17 = !DIEnumerator(name: "_ISalnum", value: 8)
!18 = !{!19, !20, !21, !22, !23}
!19 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!20 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!21 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!23 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!24 = !{!25, !31, !36, !37, !40, !45}
!25 = distinct !DISubprogram(name: "rhash_print_hex_byte", scope: !1, file: !1, line: 29, type: !26, isLocal: false, isDefinition: true, scopeLine: 30, flags: DIFlagPrototyped, isOptimized: false, variables: !30)
!26 = !DISubroutineType(types: !27)
!27 = !{!28, !28, !29, !19}
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!29 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !20)
!30 = !{}
!31 = distinct !DISubprogram(name: "rhash_byte_to_hex", scope: !1, file: !1, line: 47, type: !32, isLocal: false, isDefinition: true, scopeLine: 48, flags: DIFlagPrototyped, isOptimized: false, variables: !30)
!32 = !DISubroutineType(types: !33)
!33 = !{null, !28, !34, !35, !19}
!34 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!35 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!36 = distinct !DISubprogram(name: "rhash_byte_to_base32", scope: !1, file: !1, line: 63, type: !32, isLocal: false, isDefinition: true, scopeLine: 64, flags: DIFlagPrototyped, isOptimized: false, variables: !30)
!37 = distinct !DISubprogram(name: "rhash_byte_to_base64", scope: !1, file: !1, line: 95, type: !38, isLocal: false, isDefinition: true, scopeLine: 96, flags: DIFlagPrototyped, isOptimized: false, variables: !30)
!38 = !DISubroutineType(types: !39)
!39 = !{null, !28, !34, !35}
!40 = distinct !DISubprogram(name: "rhash_urlencode", scope: !1, file: !1, line: 134, type: !41, isLocal: false, isDefinition: true, scopeLine: 135, flags: DIFlagPrototyped, isOptimized: false, variables: !30)
!41 = !DISubroutineType(types: !42)
!42 = !{!19, !28, !43}
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !23)
!45 = distinct !DISubprogram(name: "rhash_sprintI64", scope: !1, file: !1, line: 163, type: !46, isLocal: false, isDefinition: true, scopeLine: 164, flags: DIFlagPrototyped, isOptimized: false, variables: !30)
!46 = !DISubroutineType(types: !47)
!47 = !{!19, !28, !48}
!48 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !49, line: 55, baseType: !50)
!49 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!50 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!51 = !{!52}
!52 = !DIGlobalVariable(name: "tail", scope: !37, file: !1, line: 97, type: !43, isLocal: true, isDefinition: true, variable: i8** @rhash_byte_to_base64.tail)
!53 = !{i32 2, !"Dwarf Version", i32 4}
!54 = !{i32 2, !"Debug Info Version", i32 3}
!55 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!56 = !DILocalVariable(name: "dest", arg: 1, scope: !25, file: !1, line: 29, type: !28)
!57 = !DIExpression()
!58 = !DILocation(line: 29, column: 34, scope: !25)
!59 = !DILocalVariable(name: "byte", arg: 2, scope: !25, file: !1, line: 29, type: !29)
!60 = !DILocation(line: 29, column: 60, scope: !25)
!61 = !DILocalVariable(name: "upper_case", arg: 3, scope: !25, file: !1, line: 29, type: !19)
!62 = !DILocation(line: 29, column: 70, scope: !25)
!63 = !DILocalVariable(name: "add", scope: !25, file: !1, line: 31, type: !44)
!64 = !DILocation(line: 31, column: 13, scope: !25)
!65 = !DILocation(line: 31, column: 20, scope: !25)
!66 = !DILocation(line: 31, column: 19, scope: !25)
!67 = !DILocalVariable(name: "c", scope: !25, file: !1, line: 32, type: !20)
!68 = !DILocation(line: 32, column: 16, scope: !25)
!69 = !DILocation(line: 32, column: 21, scope: !25)
!70 = !DILocation(line: 32, column: 26, scope: !25)
!71 = !DILocation(line: 32, column: 32, scope: !25)
!72 = !DILocation(line: 32, column: 20, scope: !25)
!73 = !DILocation(line: 33, column: 13, scope: !25)
!74 = !DILocation(line: 33, column: 15, scope: !25)
!75 = !DILocation(line: 33, column: 21, scope: !76)
!76 = !DILexicalBlockFile(scope: !25, file: !1, discriminator: 1)
!77 = !DILocation(line: 33, column: 25, scope: !76)
!78 = !DILocation(line: 33, column: 23, scope: !76)
!79 = !DILocation(line: 33, column: 13, scope: !76)
!80 = !DILocation(line: 33, column: 31, scope: !81)
!81 = !DILexicalBlockFile(scope: !25, file: !1, discriminator: 2)
!82 = !DILocation(line: 33, column: 33, scope: !81)
!83 = !DILocation(line: 33, column: 13, scope: !81)
!84 = !DILocation(line: 33, column: 13, scope: !85)
!85 = !DILexicalBlockFile(scope: !25, file: !1, discriminator: 3)
!86 = !DILocation(line: 33, column: 12, scope: !85)
!87 = !DILocation(line: 33, column: 7, scope: !85)
!88 = !DILocation(line: 33, column: 10, scope: !85)
!89 = !DILocation(line: 34, column: 6, scope: !25)
!90 = !DILocation(line: 34, column: 11, scope: !25)
!91 = !DILocation(line: 34, column: 4, scope: !25)
!92 = !DILocation(line: 35, column: 13, scope: !25)
!93 = !DILocation(line: 35, column: 15, scope: !25)
!94 = !DILocation(line: 35, column: 21, scope: !76)
!95 = !DILocation(line: 35, column: 25, scope: !76)
!96 = !DILocation(line: 35, column: 23, scope: !76)
!97 = !DILocation(line: 35, column: 13, scope: !76)
!98 = !DILocation(line: 35, column: 31, scope: !81)
!99 = !DILocation(line: 35, column: 33, scope: !81)
!100 = !DILocation(line: 35, column: 13, scope: !81)
!101 = !DILocation(line: 35, column: 13, scope: !85)
!102 = !DILocation(line: 35, column: 12, scope: !85)
!103 = !DILocation(line: 35, column: 7, scope: !85)
!104 = !DILocation(line: 35, column: 10, scope: !85)
!105 = !DILocation(line: 36, column: 9, scope: !25)
!106 = !DILocation(line: 36, column: 2, scope: !25)
!107 = !DILocalVariable(name: "dest", arg: 1, scope: !31, file: !1, line: 47, type: !28)
!108 = !DILocation(line: 47, column: 30, scope: !31)
!109 = !DILocalVariable(name: "src", arg: 2, scope: !31, file: !1, line: 47, type: !34)
!110 = !DILocation(line: 47, column: 57, scope: !31)
!111 = !DILocalVariable(name: "len", arg: 3, scope: !31, file: !1, line: 47, type: !35)
!112 = !DILocation(line: 47, column: 71, scope: !31)
!113 = !DILocalVariable(name: "upper_case", arg: 4, scope: !31, file: !1, line: 47, type: !19)
!114 = !DILocation(line: 47, column: 80, scope: !31)
!115 = !DILocation(line: 49, column: 2, scope: !31)
!116 = !DILocation(line: 49, column: 12, scope: !117)
!117 = !DILexicalBlockFile(scope: !31, file: !1, discriminator: 1)
!118 = !DILocation(line: 49, column: 15, scope: !117)
!119 = !DILocation(line: 49, column: 2, scope: !117)
!120 = !DILocation(line: 50, column: 31, scope: !121)
!121 = distinct !DILexicalBlock(scope: !31, file: !1, line: 49, column: 20)
!122 = !DILocation(line: 50, column: 41, scope: !121)
!123 = !DILocation(line: 50, column: 37, scope: !121)
!124 = !DILocation(line: 50, column: 45, scope: !121)
!125 = !DILocation(line: 50, column: 10, scope: !121)
!126 = !DILocation(line: 50, column: 8, scope: !121)
!127 = !DILocation(line: 49, column: 2, scope: !128)
!128 = !DILexicalBlockFile(scope: !31, file: !1, discriminator: 2)
!129 = !DILocation(line: 52, column: 3, scope: !31)
!130 = !DILocation(line: 52, column: 8, scope: !31)
!131 = !DILocation(line: 53, column: 1, scope: !31)
!132 = !DILocalVariable(name: "dest", arg: 1, scope: !36, file: !1, line: 63, type: !28)
!133 = !DILocation(line: 63, column: 33, scope: !36)
!134 = !DILocalVariable(name: "src", arg: 2, scope: !36, file: !1, line: 63, type: !34)
!135 = !DILocation(line: 63, column: 60, scope: !36)
!136 = !DILocalVariable(name: "len", arg: 3, scope: !36, file: !1, line: 63, type: !35)
!137 = !DILocation(line: 63, column: 74, scope: !36)
!138 = !DILocalVariable(name: "upper_case", arg: 4, scope: !36, file: !1, line: 63, type: !19)
!139 = !DILocation(line: 63, column: 83, scope: !36)
!140 = !DILocalVariable(name: "a", scope: !36, file: !1, line: 65, type: !44)
!141 = !DILocation(line: 65, column: 13, scope: !36)
!142 = !DILocation(line: 65, column: 18, scope: !36)
!143 = !DILocation(line: 65, column: 17, scope: !36)
!144 = !DILocalVariable(name: "shift", scope: !36, file: !1, line: 66, type: !35)
!145 = !DILocation(line: 66, column: 11, scope: !36)
!146 = !DILocalVariable(name: "word", scope: !36, file: !1, line: 67, type: !20)
!147 = !DILocation(line: 67, column: 16, scope: !36)
!148 = !DILocalVariable(name: "e", scope: !36, file: !1, line: 68, type: !34)
!149 = !DILocation(line: 68, column: 23, scope: !36)
!150 = !DILocation(line: 68, column: 27, scope: !36)
!151 = !DILocation(line: 68, column: 33, scope: !36)
!152 = !DILocation(line: 68, column: 31, scope: !36)
!153 = !DILocation(line: 69, column: 2, scope: !36)
!154 = !DILocation(line: 69, column: 9, scope: !155)
!155 = !DILexicalBlockFile(scope: !36, file: !1, discriminator: 1)
!156 = !DILocation(line: 69, column: 15, scope: !155)
!157 = !DILocation(line: 69, column: 13, scope: !155)
!158 = !DILocation(line: 69, column: 2, scope: !155)
!159 = !DILocation(line: 70, column: 7, scope: !160)
!160 = distinct !DILexicalBlock(scope: !161, file: !1, line: 70, column: 7)
!161 = distinct !DILexicalBlock(scope: !36, file: !1, line: 69, column: 18)
!162 = !DILocation(line: 70, column: 13, scope: !160)
!163 = !DILocation(line: 70, column: 7, scope: !161)
!164 = !DILocation(line: 71, column: 13, scope: !165)
!165 = distinct !DILexicalBlock(scope: !160, file: !1, line: 70, column: 18)
!166 = !DILocation(line: 71, column: 12, scope: !165)
!167 = !DILocation(line: 71, column: 28, scope: !165)
!168 = !DILocation(line: 71, column: 25, scope: !165)
!169 = !DILocation(line: 71, column: 17, scope: !165)
!170 = !DILocation(line: 71, column: 11, scope: !165)
!171 = !DILocation(line: 71, column: 9, scope: !165)
!172 = !DILocation(line: 72, column: 13, scope: !165)
!173 = !DILocation(line: 72, column: 19, scope: !165)
!174 = !DILocation(line: 72, column: 24, scope: !165)
!175 = !DILocation(line: 72, column: 10, scope: !165)
!176 = !DILocation(line: 73, column: 13, scope: !165)
!177 = !DILocation(line: 73, column: 9, scope: !165)
!178 = !DILocation(line: 74, column: 8, scope: !179)
!179 = distinct !DILexicalBlock(scope: !165, file: !1, line: 74, column: 8)
!180 = !DILocation(line: 74, column: 12, scope: !179)
!181 = !DILocation(line: 74, column: 18, scope: !179)
!182 = !DILocation(line: 74, column: 16, scope: !179)
!183 = !DILocation(line: 74, column: 8, scope: !165)
!184 = !DILocation(line: 75, column: 15, scope: !179)
!185 = !DILocation(line: 75, column: 19, scope: !179)
!186 = !DILocation(line: 75, column: 13, scope: !179)
!187 = !DILocation(line: 75, column: 32, scope: !179)
!188 = !DILocation(line: 75, column: 30, scope: !179)
!189 = !DILocation(line: 75, column: 24, scope: !179)
!190 = !DILocation(line: 75, column: 10, scope: !179)
!191 = !DILocation(line: 75, column: 5, scope: !179)
!192 = !DILocation(line: 76, column: 4, scope: !165)
!193 = !DILocation(line: 77, column: 3, scope: !165)
!194 = !DILocation(line: 78, column: 13, scope: !195)
!195 = distinct !DILexicalBlock(scope: !160, file: !1, line: 77, column: 10)
!196 = !DILocation(line: 78, column: 19, scope: !195)
!197 = !DILocation(line: 78, column: 24, scope: !195)
!198 = !DILocation(line: 78, column: 10, scope: !195)
!199 = !DILocation(line: 79, column: 14, scope: !195)
!200 = !DILocation(line: 79, column: 13, scope: !195)
!201 = !DILocation(line: 79, column: 28, scope: !195)
!202 = !DILocation(line: 79, column: 26, scope: !195)
!203 = !DILocation(line: 79, column: 35, scope: !195)
!204 = !DILocation(line: 79, column: 18, scope: !195)
!205 = !DILocation(line: 79, column: 43, scope: !195)
!206 = !DILocation(line: 79, column: 11, scope: !195)
!207 = !DILocation(line: 79, column: 9, scope: !195)
!208 = !DILocation(line: 80, column: 8, scope: !209)
!209 = distinct !DILexicalBlock(scope: !195, file: !1, line: 80, column: 8)
!210 = !DILocation(line: 80, column: 14, scope: !209)
!211 = !DILocation(line: 80, column: 8, scope: !195)
!212 = !DILocation(line: 80, column: 23, scope: !213)
!213 = !DILexicalBlockFile(scope: !209, file: !1, discriminator: 1)
!214 = !DILocation(line: 80, column: 20, scope: !213)
!215 = !DILocation(line: 82, column: 15, scope: !161)
!216 = !DILocation(line: 82, column: 20, scope: !161)
!217 = !DILocation(line: 82, column: 27, scope: !218)
!218 = !DILexicalBlockFile(scope: !161, file: !1, discriminator: 1)
!219 = !DILocation(line: 82, column: 34, scope: !218)
!220 = !DILocation(line: 82, column: 32, scope: !218)
!221 = !DILocation(line: 82, column: 15, scope: !218)
!222 = !DILocation(line: 82, column: 38, scope: !223)
!223 = !DILexicalBlockFile(scope: !161, file: !1, discriminator: 2)
!224 = !DILocation(line: 82, column: 43, scope: !223)
!225 = !DILocation(line: 82, column: 49, scope: !223)
!226 = !DILocation(line: 82, column: 15, scope: !223)
!227 = !DILocation(line: 82, column: 15, scope: !228)
!228 = !DILexicalBlockFile(scope: !161, file: !1, discriminator: 3)
!229 = !DILocation(line: 82, column: 13, scope: !228)
!230 = !DILocation(line: 82, column: 8, scope: !228)
!231 = !DILocation(line: 82, column: 11, scope: !228)
!232 = !DILocation(line: 69, column: 2, scope: !233)
!233 = !DILexicalBlockFile(scope: !36, file: !1, discriminator: 2)
!234 = !DILocation(line: 84, column: 3, scope: !36)
!235 = !DILocation(line: 84, column: 8, scope: !36)
!236 = !DILocation(line: 85, column: 1, scope: !36)
!237 = !DILocalVariable(name: "dest", arg: 1, scope: !37, file: !1, line: 95, type: !28)
!238 = !DILocation(line: 95, column: 33, scope: !37)
!239 = !DILocalVariable(name: "src", arg: 2, scope: !37, file: !1, line: 95, type: !34)
!240 = !DILocation(line: 95, column: 60, scope: !37)
!241 = !DILocalVariable(name: "len", arg: 3, scope: !37, file: !1, line: 95, type: !35)
!242 = !DILocation(line: 95, column: 74, scope: !37)
!243 = !DILocalVariable(name: "shift", scope: !37, file: !1, line: 98, type: !35)
!244 = !DILocation(line: 98, column: 11, scope: !37)
!245 = !DILocalVariable(name: "word", scope: !37, file: !1, line: 99, type: !20)
!246 = !DILocation(line: 99, column: 16, scope: !37)
!247 = !DILocalVariable(name: "e", scope: !37, file: !1, line: 100, type: !34)
!248 = !DILocation(line: 100, column: 23, scope: !37)
!249 = !DILocation(line: 100, column: 27, scope: !37)
!250 = !DILocation(line: 100, column: 33, scope: !37)
!251 = !DILocation(line: 100, column: 31, scope: !37)
!252 = !DILocation(line: 101, column: 2, scope: !37)
!253 = !DILocation(line: 101, column: 9, scope: !254)
!254 = !DILexicalBlockFile(scope: !37, file: !1, discriminator: 1)
!255 = !DILocation(line: 101, column: 15, scope: !254)
!256 = !DILocation(line: 101, column: 13, scope: !254)
!257 = !DILocation(line: 101, column: 2, scope: !254)
!258 = !DILocation(line: 102, column: 7, scope: !259)
!259 = distinct !DILexicalBlock(scope: !260, file: !1, line: 102, column: 7)
!260 = distinct !DILexicalBlock(scope: !37, file: !1, line: 101, column: 18)
!261 = !DILocation(line: 102, column: 13, scope: !259)
!262 = !DILocation(line: 102, column: 7, scope: !260)
!263 = !DILocation(line: 103, column: 13, scope: !264)
!264 = distinct !DILexicalBlock(scope: !259, file: !1, line: 102, column: 18)
!265 = !DILocation(line: 103, column: 12, scope: !264)
!266 = !DILocation(line: 103, column: 28, scope: !264)
!267 = !DILocation(line: 103, column: 25, scope: !264)
!268 = !DILocation(line: 103, column: 17, scope: !264)
!269 = !DILocation(line: 103, column: 11, scope: !264)
!270 = !DILocation(line: 103, column: 9, scope: !264)
!271 = !DILocation(line: 104, column: 13, scope: !264)
!272 = !DILocation(line: 104, column: 19, scope: !264)
!273 = !DILocation(line: 104, column: 24, scope: !264)
!274 = !DILocation(line: 104, column: 10, scope: !264)
!275 = !DILocation(line: 105, column: 13, scope: !264)
!276 = !DILocation(line: 105, column: 9, scope: !264)
!277 = !DILocation(line: 106, column: 8, scope: !278)
!278 = distinct !DILexicalBlock(scope: !264, file: !1, line: 106, column: 8)
!279 = !DILocation(line: 106, column: 12, scope: !278)
!280 = !DILocation(line: 106, column: 18, scope: !278)
!281 = !DILocation(line: 106, column: 16, scope: !278)
!282 = !DILocation(line: 106, column: 8, scope: !264)
!283 = !DILocation(line: 107, column: 15, scope: !278)
!284 = !DILocation(line: 107, column: 19, scope: !278)
!285 = !DILocation(line: 107, column: 13, scope: !278)
!286 = !DILocation(line: 107, column: 32, scope: !278)
!287 = !DILocation(line: 107, column: 30, scope: !278)
!288 = !DILocation(line: 107, column: 24, scope: !278)
!289 = !DILocation(line: 107, column: 10, scope: !278)
!290 = !DILocation(line: 107, column: 5, scope: !278)
!291 = !DILocation(line: 108, column: 4, scope: !264)
!292 = !DILocation(line: 109, column: 3, scope: !264)
!293 = !DILocation(line: 110, column: 13, scope: !294)
!294 = distinct !DILexicalBlock(scope: !259, file: !1, line: 109, column: 10)
!295 = !DILocation(line: 110, column: 19, scope: !294)
!296 = !DILocation(line: 110, column: 24, scope: !294)
!297 = !DILocation(line: 110, column: 10, scope: !294)
!298 = !DILocation(line: 111, column: 14, scope: !294)
!299 = !DILocation(line: 111, column: 13, scope: !294)
!300 = !DILocation(line: 111, column: 28, scope: !294)
!301 = !DILocation(line: 111, column: 26, scope: !294)
!302 = !DILocation(line: 111, column: 35, scope: !294)
!303 = !DILocation(line: 111, column: 18, scope: !294)
!304 = !DILocation(line: 111, column: 43, scope: !294)
!305 = !DILocation(line: 111, column: 11, scope: !294)
!306 = !DILocation(line: 111, column: 9, scope: !294)
!307 = !DILocation(line: 112, column: 8, scope: !308)
!308 = distinct !DILexicalBlock(scope: !294, file: !1, line: 112, column: 8)
!309 = !DILocation(line: 112, column: 14, scope: !308)
!310 = !DILocation(line: 112, column: 8, scope: !294)
!311 = !DILocation(line: 112, column: 23, scope: !312)
!312 = !DILexicalBlockFile(scope: !308, file: !1, discriminator: 1)
!313 = !DILocation(line: 112, column: 20, scope: !312)
!314 = !DILocation(line: 114, column: 15, scope: !260)
!315 = !DILocation(line: 114, column: 20, scope: !260)
!316 = !DILocation(line: 114, column: 28, scope: !317)
!317 = !DILexicalBlockFile(scope: !260, file: !1, discriminator: 1)
!318 = !DILocation(line: 114, column: 33, scope: !317)
!319 = !DILocation(line: 114, column: 40, scope: !320)
!320 = !DILexicalBlockFile(scope: !260, file: !1, discriminator: 2)
!321 = !DILocation(line: 114, column: 45, scope: !320)
!322 = !DILocation(line: 114, column: 28, scope: !320)
!323 = !DILocation(line: 114, column: 53, scope: !324)
!324 = !DILexicalBlockFile(scope: !260, file: !1, discriminator: 3)
!325 = !DILocation(line: 114, column: 58, scope: !324)
!326 = !DILocation(line: 114, column: 63, scope: !324)
!327 = !DILocation(line: 114, column: 28, scope: !324)
!328 = !DILocation(line: 114, column: 28, scope: !329)
!329 = !DILexicalBlockFile(scope: !260, file: !1, discriminator: 4)
!330 = !DILocation(line: 114, column: 15, scope: !329)
!331 = !DILocation(line: 114, column: 77, scope: !332)
!332 = !DILexicalBlockFile(scope: !260, file: !1, discriminator: 5)
!333 = !DILocation(line: 114, column: 82, scope: !332)
!334 = !DILocation(line: 114, column: 72, scope: !332)
!335 = !DILocation(line: 114, column: 15, scope: !332)
!336 = !DILocation(line: 114, column: 15, scope: !337)
!337 = !DILexicalBlockFile(scope: !260, file: !1, discriminator: 6)
!338 = !DILocation(line: 114, column: 13, scope: !337)
!339 = !DILocation(line: 114, column: 8, scope: !337)
!340 = !DILocation(line: 114, column: 11, scope: !337)
!341 = !DILocation(line: 101, column: 2, scope: !342)
!342 = !DILexicalBlockFile(scope: !37, file: !1, discriminator: 2)
!343 = !DILocation(line: 116, column: 6, scope: !344)
!344 = distinct !DILexicalBlock(scope: !37, file: !1, line: 116, column: 6)
!345 = !DILocation(line: 116, column: 12, scope: !344)
!346 = !DILocation(line: 116, column: 6, scope: !37)
!347 = !DILocation(line: 117, column: 8, scope: !348)
!348 = distinct !DILexicalBlock(scope: !344, file: !1, line: 116, column: 17)
!349 = !DILocation(line: 117, column: 11, scope: !348)
!350 = !DILocation(line: 118, column: 7, scope: !351)
!351 = distinct !DILexicalBlock(scope: !348, file: !1, line: 118, column: 7)
!352 = !DILocation(line: 118, column: 13, scope: !351)
!353 = !DILocation(line: 118, column: 7, scope: !348)
!354 = !DILocation(line: 118, column: 24, scope: !355)
!355 = !DILexicalBlockFile(scope: !351, file: !1, discriminator: 1)
!356 = !DILocation(line: 118, column: 27, scope: !355)
!357 = !DILocation(line: 118, column: 19, scope: !355)
!358 = !DILocation(line: 119, column: 2, scope: !348)
!359 = !DILocation(line: 120, column: 3, scope: !37)
!360 = !DILocation(line: 120, column: 8, scope: !37)
!361 = !DILocation(line: 121, column: 1, scope: !37)
!362 = !DILocalVariable(name: "dst", arg: 1, scope: !40, file: !1, line: 134, type: !28)
!363 = !DILocation(line: 134, column: 27, scope: !40)
!364 = !DILocalVariable(name: "name", arg: 2, scope: !40, file: !1, line: 134, type: !43)
!365 = !DILocation(line: 134, column: 44, scope: !40)
!366 = !DILocalVariable(name: "start", scope: !40, file: !1, line: 136, type: !43)
!367 = !DILocation(line: 136, column: 14, scope: !40)
!368 = !DILocation(line: 137, column: 7, scope: !369)
!369 = distinct !DILexicalBlock(scope: !40, file: !1, line: 137, column: 6)
!370 = !DILocation(line: 137, column: 6, scope: !40)
!371 = !DILocalVariable(name: "len", scope: !372, file: !1, line: 138, type: !19)
!372 = distinct !DILexicalBlock(scope: !369, file: !1, line: 137, column: 12)
!373 = !DILocation(line: 138, column: 7, scope: !372)
!374 = !DILocation(line: 139, column: 12, scope: !375)
!375 = distinct !DILexicalBlock(scope: !372, file: !1, line: 139, column: 3)
!376 = !DILocation(line: 139, column: 8, scope: !375)
!377 = !DILocation(line: 139, column: 18, scope: !378)
!378 = !DILexicalBlockFile(scope: !379, file: !1, discriminator: 1)
!379 = distinct !DILexicalBlock(scope: !375, file: !1, line: 139, column: 3)
!380 = !DILocation(line: 139, column: 17, scope: !378)
!381 = !DILocation(line: 139, column: 3, scope: !378)
!382 = !DILocation(line: 139, column: 40, scope: !383)
!383 = !DILexicalBlockFile(scope: !379, file: !1, discriminator: 2)
!384 = !DILocation(line: 139, column: 40, scope: !385)
!385 = !DILexicalBlockFile(scope: !379, file: !1, discriminator: 3)
!386 = !DILocation(line: 139, column: 40, scope: !387)
!387 = !DILexicalBlockFile(scope: !379, file: !1, discriminator: 4)
!388 = !DILocation(line: 139, column: 36, scope: !387)
!389 = !DILocation(line: 139, column: 32, scope: !387)
!390 = !DILocation(line: 139, column: 28, scope: !391)
!391 = !DILexicalBlockFile(scope: !379, file: !1, discriminator: 5)
!392 = !DILocation(line: 139, column: 3, scope: !391)
!393 = !DILocation(line: 140, column: 10, scope: !372)
!394 = !DILocation(line: 140, column: 3, scope: !372)
!395 = !DILocation(line: 143, column: 15, scope: !396)
!396 = distinct !DILexicalBlock(scope: !40, file: !1, line: 143, column: 2)
!397 = !DILocation(line: 143, column: 13, scope: !396)
!398 = !DILocation(line: 143, column: 7, scope: !396)
!399 = !DILocation(line: 143, column: 21, scope: !400)
!400 = !DILexicalBlockFile(scope: !401, file: !1, discriminator: 1)
!401 = distinct !DILexicalBlock(scope: !396, file: !1, line: 143, column: 2)
!402 = !DILocation(line: 143, column: 20, scope: !400)
!403 = !DILocation(line: 143, column: 2, scope: !400)
!404 = !DILocation(line: 144, column: 8, scope: !405)
!405 = distinct !DILexicalBlock(scope: !406, file: !1, line: 144, column: 8)
!406 = distinct !DILexicalBlock(scope: !401, file: !1, line: 143, column: 35)
!407 = !DILocation(line: 144, column: 8, scope: !408)
!408 = !DILexicalBlockFile(scope: !405, file: !1, discriminator: 1)
!409 = !DILocation(line: 145, column: 14, scope: !410)
!410 = distinct !DILexicalBlock(scope: !405, file: !1, line: 144, column: 34)
!411 = !DILocation(line: 145, column: 13, scope: !410)
!412 = !DILocation(line: 145, column: 8, scope: !410)
!413 = !DILocation(line: 145, column: 11, scope: !410)
!414 = !DILocation(line: 146, column: 3, scope: !410)
!415 = !DILocation(line: 147, column: 8, scope: !416)
!416 = distinct !DILexicalBlock(scope: !405, file: !1, line: 146, column: 10)
!417 = !DILocation(line: 147, column: 11, scope: !416)
!418 = !DILocation(line: 148, column: 31, scope: !416)
!419 = !DILocation(line: 148, column: 37, scope: !416)
!420 = !DILocation(line: 148, column: 36, scope: !416)
!421 = !DILocation(line: 148, column: 10, scope: !416)
!422 = !DILocation(line: 148, column: 8, scope: !416)
!423 = !DILocation(line: 150, column: 2, scope: !406)
!424 = !DILocation(line: 143, column: 31, scope: !425)
!425 = !DILexicalBlockFile(scope: !401, file: !1, discriminator: 2)
!426 = !DILocation(line: 143, column: 2, scope: !425)
!427 = !DILocation(line: 151, column: 3, scope: !40)
!428 = !DILocation(line: 151, column: 7, scope: !40)
!429 = !DILocation(line: 152, column: 15, scope: !40)
!430 = !DILocation(line: 152, column: 21, scope: !40)
!431 = !DILocation(line: 152, column: 19, scope: !40)
!432 = !DILocation(line: 152, column: 9, scope: !40)
!433 = !DILocation(line: 152, column: 2, scope: !40)
!434 = !DILocation(line: 153, column: 1, scope: !40)
!435 = !DILocalVariable(name: "dst", arg: 1, scope: !45, file: !1, line: 163, type: !28)
!436 = !DILocation(line: 163, column: 27, scope: !45)
!437 = !DILocalVariable(name: "number", arg: 2, scope: !45, file: !1, line: 163, type: !48)
!438 = !DILocation(line: 163, column: 41, scope: !45)
!439 = !DILocalVariable(name: "buf", scope: !45, file: !1, line: 166, type: !440)
!440 = !DICompositeType(tag: DW_TAG_array_type, baseType: !23, size: 192, align: 8, elements: !441)
!441 = !{!442}
!442 = !DISubrange(count: 24)
!443 = !DILocation(line: 166, column: 7, scope: !45)
!444 = !DILocalVariable(name: "p", scope: !45, file: !1, line: 166, type: !28)
!445 = !DILocation(line: 166, column: 17, scope: !45)
!446 = !DILocalVariable(name: "length", scope: !45, file: !1, line: 167, type: !447)
!447 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !448, line: 62, baseType: !50)
!448 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!449 = !DILocation(line: 167, column: 9, scope: !45)
!450 = !DILocation(line: 169, column: 6, scope: !451)
!451 = distinct !DILexicalBlock(scope: !45, file: !1, line: 169, column: 6)
!452 = !DILocation(line: 169, column: 10, scope: !451)
!453 = !DILocation(line: 169, column: 6, scope: !45)
!454 = !DILocation(line: 171, column: 7, scope: !455)
!455 = distinct !DILexicalBlock(scope: !456, file: !1, line: 171, column: 7)
!456 = distinct !DILexicalBlock(scope: !451, file: !1, line: 169, column: 19)
!457 = !DILocation(line: 171, column: 14, scope: !455)
!458 = !DILocation(line: 171, column: 7, scope: !456)
!459 = !DILocation(line: 171, column: 20, scope: !460)
!460 = !DILexicalBlockFile(scope: !455, file: !1, discriminator: 1)
!461 = !DILocation(line: 172, column: 15, scope: !462)
!462 = distinct !DILexicalBlock(scope: !456, file: !1, line: 172, column: 3)
!463 = !DILocation(line: 172, column: 8, scope: !462)
!464 = !DILocation(line: 172, column: 20, scope: !465)
!465 = !DILexicalBlockFile(scope: !466, file: !1, discriminator: 1)
!466 = distinct !DILexicalBlock(scope: !462, file: !1, line: 172, column: 3)
!467 = !DILocation(line: 172, column: 27, scope: !465)
!468 = !DILocation(line: 172, column: 3, scope: !465)
!469 = !DILocation(line: 172, column: 53, scope: !470)
!470 = !DILexicalBlockFile(scope: !466, file: !1, discriminator: 2)
!471 = !DILocation(line: 172, column: 47, scope: !470)
!472 = !DILocation(line: 172, column: 40, scope: !473)
!473 = !DILexicalBlockFile(scope: !466, file: !1, discriminator: 3)
!474 = !DILocation(line: 172, column: 3, scope: !473)
!475 = !DILocation(line: 173, column: 15, scope: !456)
!476 = !DILocation(line: 173, column: 10, scope: !456)
!477 = !DILocation(line: 173, column: 3, scope: !456)
!478 = !DILocation(line: 176, column: 6, scope: !45)
!479 = !DILocation(line: 176, column: 10, scope: !45)
!480 = !DILocation(line: 176, column: 4, scope: !45)
!481 = !DILocation(line: 177, column: 3, scope: !45)
!482 = !DILocation(line: 177, column: 5, scope: !45)
!483 = !DILocation(line: 178, column: 6, scope: !484)
!484 = distinct !DILexicalBlock(scope: !45, file: !1, line: 178, column: 6)
!485 = !DILocation(line: 178, column: 13, scope: !484)
!486 = !DILocation(line: 178, column: 6, scope: !45)
!487 = !DILocation(line: 179, column: 5, scope: !488)
!488 = distinct !DILexicalBlock(scope: !484, file: !1, line: 178, column: 19)
!489 = !DILocation(line: 179, column: 10, scope: !488)
!490 = !DILocation(line: 180, column: 2, scope: !488)
!491 = !DILocation(line: 181, column: 3, scope: !492)
!492 = distinct !DILexicalBlock(scope: !484, file: !1, line: 180, column: 9)
!493 = !DILocation(line: 181, column: 10, scope: !494)
!494 = !DILexicalBlockFile(scope: !495, file: !1, discriminator: 1)
!495 = distinct !DILexicalBlock(scope: !496, file: !1, line: 181, column: 3)
!496 = distinct !DILexicalBlock(scope: !492, file: !1, line: 181, column: 3)
!497 = !DILocation(line: 181, column: 15, scope: !494)
!498 = !DILocation(line: 181, column: 12, scope: !494)
!499 = !DILocation(line: 181, column: 19, scope: !494)
!500 = !DILocation(line: 181, column: 22, scope: !501)
!501 = !DILexicalBlockFile(scope: !495, file: !1, discriminator: 2)
!502 = !DILocation(line: 181, column: 29, scope: !501)
!503 = !DILocation(line: 181, column: 3, scope: !504)
!504 = !DILexicalBlockFile(scope: !496, file: !1, discriminator: 3)
!505 = !DILocation(line: 182, column: 26, scope: !506)
!506 = distinct !DILexicalBlock(scope: !495, file: !1, line: 181, column: 49)
!507 = !DILocation(line: 182, column: 33, scope: !506)
!508 = !DILocation(line: 182, column: 19, scope: !506)
!509 = !DILocation(line: 182, column: 17, scope: !506)
!510 = !DILocation(line: 182, column: 13, scope: !506)
!511 = !DILocation(line: 182, column: 6, scope: !506)
!512 = !DILocation(line: 182, column: 11, scope: !506)
!513 = !DILocation(line: 183, column: 3, scope: !506)
!514 = !DILocation(line: 181, column: 42, scope: !515)
!515 = !DILexicalBlockFile(scope: !495, file: !1, discriminator: 4)
!516 = !DILocation(line: 181, column: 3, scope: !515)
!517 = !DILocation(line: 185, column: 11, scope: !45)
!518 = !DILocation(line: 185, column: 15, scope: !45)
!519 = !DILocation(line: 185, column: 22, scope: !45)
!520 = !DILocation(line: 185, column: 20, scope: !45)
!521 = !DILocation(line: 185, column: 9, scope: !45)
!522 = !DILocation(line: 186, column: 9, scope: !45)
!523 = !DILocation(line: 186, column: 14, scope: !45)
!524 = !DILocation(line: 186, column: 17, scope: !45)
!525 = !DILocation(line: 186, column: 24, scope: !45)
!526 = !DILocation(line: 186, column: 2, scope: !45)
!527 = !DILocation(line: 187, column: 14, scope: !45)
!528 = !DILocation(line: 187, column: 9, scope: !45)
!529 = !DILocation(line: 187, column: 2, scope: !45)
!530 = !DILocation(line: 188, column: 1, scope: !45)
