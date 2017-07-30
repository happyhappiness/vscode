; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/byte_order.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define void @rhash_swap_copy_str_to_u32(i8* %to, i32 %index, i8* %from, i64 %length) #0 !dbg !23 {
entry:
  %to.addr = alloca i8*, align 8
  %index.addr = alloca i32, align 4
  %from.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %src = alloca i32*, align 8
  %end = alloca i32*, align 8
  %dst = alloca i32*, align 8
  %src12 = alloca i8*, align 8
  store i8* %to, i8** %to.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %to.addr, metadata !40, metadata !41), !dbg !42
  store i32 %index, i32* %index.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %index.addr, metadata !43, metadata !41), !dbg !44
  store i8* %from, i8** %from.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %from.addr, metadata !45, metadata !41), !dbg !46
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !47, metadata !41), !dbg !48
  %0 = load i8*, i8** %to.addr, align 8, !dbg !49
  %sub.ptr.lhs.cast = ptrtoint i8* %0 to i64, !dbg !51
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, 0, !dbg !51
  %conv = trunc i64 %sub.ptr.sub to i32, !dbg !52
  %conv1 = sext i32 %conv to i64, !dbg !52
  %1 = load i8*, i8** %from.addr, align 8, !dbg !53
  %sub.ptr.lhs.cast2 = ptrtoint i8* %1 to i64, !dbg !54
  %sub.ptr.sub3 = sub i64 %sub.ptr.lhs.cast2, 0, !dbg !54
  %or = or i64 %conv1, %sub.ptr.sub3, !dbg !55
  %2 = load i32, i32* %index.addr, align 4, !dbg !56
  %conv4 = sext i32 %2 to i64, !dbg !56
  %or5 = or i64 %or, %conv4, !dbg !57
  %3 = load i64, i64* %length.addr, align 8, !dbg !58
  %or6 = or i64 %or5, %3, !dbg !59
  %and = and i64 %or6, 3, !dbg !60
  %cmp = icmp eq i64 0, %and, !dbg !61
  br i1 %cmp, label %if.then, label %if.else, !dbg !62

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32** %src, metadata !63, metadata !41), !dbg !65
  %4 = load i8*, i8** %from.addr, align 8, !dbg !66
  %5 = bitcast i8* %4 to i32*, !dbg !67
  store i32* %5, i32** %src, align 8, !dbg !65
  call void @llvm.dbg.declare(metadata i32** %end, metadata !68, metadata !41), !dbg !69
  %6 = load i32*, i32** %src, align 8, !dbg !70
  %7 = bitcast i32* %6 to i8*, !dbg !71
  %8 = load i64, i64* %length.addr, align 8, !dbg !72
  %add.ptr = getelementptr inbounds i8, i8* %7, i64 %8, !dbg !73
  %9 = bitcast i8* %add.ptr to i32*, !dbg !74
  store i32* %9, i32** %end, align 8, !dbg !69
  call void @llvm.dbg.declare(metadata i32** %dst, metadata !75, metadata !41), !dbg !76
  %10 = load i8*, i8** %to.addr, align 8, !dbg !77
  %11 = load i32, i32* %index.addr, align 4, !dbg !78
  %idx.ext = sext i32 %11 to i64, !dbg !79
  %add.ptr8 = getelementptr inbounds i8, i8* %10, i64 %idx.ext, !dbg !79
  %12 = bitcast i8* %add.ptr8 to i32*, !dbg !80
  store i32* %12, i32** %dst, align 8, !dbg !76
  br label %while.cond, !dbg !81

while.cond:                                       ; preds = %while.body, %if.then
  %13 = load i32*, i32** %src, align 8, !dbg !82
  %14 = load i32*, i32** %end, align 8, !dbg !84
  %cmp9 = icmp ult i32* %13, %14, !dbg !85
  br i1 %cmp9, label %while.body, label %while.end, !dbg !86

while.body:                                       ; preds = %while.cond
  %15 = load i32*, i32** %src, align 8, !dbg !87
  %incdec.ptr = getelementptr inbounds i32, i32* %15, i32 1, !dbg !87
  store i32* %incdec.ptr, i32** %src, align 8, !dbg !87
  %16 = load i32, i32* %15, align 4, !dbg !87
  %17 = call i32 @llvm.bswap.i32(i32 %16), !dbg !87
  %18 = load i32*, i32** %dst, align 8, !dbg !89
  %incdec.ptr11 = getelementptr inbounds i32, i32* %18, i32 1, !dbg !89
  store i32* %incdec.ptr11, i32** %dst, align 8, !dbg !89
  store i32 %17, i32* %18, align 4, !dbg !90
  br label %while.cond, !dbg !91

while.end:                                        ; preds = %while.cond
  br label %if.end, !dbg !92

if.else:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i8** %src12, metadata !93, metadata !41), !dbg !95
  %19 = load i8*, i8** %from.addr, align 8, !dbg !96
  store i8* %19, i8** %src12, align 8, !dbg !95
  %20 = load i32, i32* %index.addr, align 4, !dbg !97
  %conv13 = sext i32 %20 to i64, !dbg !97
  %21 = load i64, i64* %length.addr, align 8, !dbg !99
  %add = add i64 %21, %conv13, !dbg !99
  store i64 %add, i64* %length.addr, align 8, !dbg !99
  br label %for.cond, !dbg !100

for.cond:                                         ; preds = %for.inc, %if.else
  %22 = load i32, i32* %index.addr, align 4, !dbg !101
  %conv14 = sext i32 %22 to i64, !dbg !104
  %23 = load i64, i64* %length.addr, align 8, !dbg !105
  %cmp15 = icmp ult i64 %conv14, %23, !dbg !106
  br i1 %cmp15, label %for.body, label %for.end, !dbg !107

for.body:                                         ; preds = %for.cond
  %24 = load i8*, i8** %src12, align 8, !dbg !108
  %incdec.ptr17 = getelementptr inbounds i8, i8* %24, i32 1, !dbg !108
  store i8* %incdec.ptr17, i8** %src12, align 8, !dbg !108
  %25 = load i8, i8* %24, align 1, !dbg !110
  %26 = load i32, i32* %index.addr, align 4, !dbg !111
  %xor = xor i32 %26, 3, !dbg !112
  %idxprom = sext i32 %xor to i64, !dbg !113
  %27 = load i8*, i8** %to.addr, align 8, !dbg !114
  %arrayidx = getelementptr inbounds i8, i8* %27, i64 %idxprom, !dbg !113
  store i8 %25, i8* %arrayidx, align 1, !dbg !115
  br label %for.inc, !dbg !113

for.inc:                                          ; preds = %for.body
  %28 = load i32, i32* %index.addr, align 4, !dbg !116
  %inc = add nsw i32 %28, 1, !dbg !116
  store i32 %inc, i32* %index.addr, align 4, !dbg !116
  br label %for.cond, !dbg !118

for.end:                                          ; preds = %for.cond
  br label %if.end

if.end:                                           ; preds = %for.end, %while.end
  ret void, !dbg !119
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readnone
declare i32 @llvm.bswap.i32(i32) #1

; Function Attrs: nounwind uwtable
define void @rhash_swap_copy_str_to_u64(i8* %to, i32 %index, i8* %from, i64 %length) #0 !dbg !29 {
entry:
  %to.addr = alloca i8*, align 8
  %index.addr = alloca i32, align 4
  %from.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %src = alloca i64*, align 8
  %end = alloca i64*, align 8
  %dst = alloca i64*, align 8
  %src12 = alloca i8*, align 8
  store i8* %to, i8** %to.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %to.addr, metadata !120, metadata !41), !dbg !121
  store i32 %index, i32* %index.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %index.addr, metadata !122, metadata !41), !dbg !123
  store i8* %from, i8** %from.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %from.addr, metadata !124, metadata !41), !dbg !125
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !126, metadata !41), !dbg !127
  %0 = load i8*, i8** %to.addr, align 8, !dbg !128
  %sub.ptr.lhs.cast = ptrtoint i8* %0 to i64, !dbg !130
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, 0, !dbg !130
  %conv = trunc i64 %sub.ptr.sub to i32, !dbg !131
  %conv1 = sext i32 %conv to i64, !dbg !131
  %1 = load i8*, i8** %from.addr, align 8, !dbg !132
  %sub.ptr.lhs.cast2 = ptrtoint i8* %1 to i64, !dbg !133
  %sub.ptr.sub3 = sub i64 %sub.ptr.lhs.cast2, 0, !dbg !133
  %or = or i64 %conv1, %sub.ptr.sub3, !dbg !134
  %2 = load i32, i32* %index.addr, align 4, !dbg !135
  %conv4 = sext i32 %2 to i64, !dbg !135
  %or5 = or i64 %or, %conv4, !dbg !136
  %3 = load i64, i64* %length.addr, align 8, !dbg !137
  %or6 = or i64 %or5, %3, !dbg !138
  %and = and i64 %or6, 7, !dbg !139
  %cmp = icmp eq i64 0, %and, !dbg !140
  br i1 %cmp, label %if.then, label %if.else, !dbg !141

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i64** %src, metadata !142, metadata !41), !dbg !144
  %4 = load i8*, i8** %from.addr, align 8, !dbg !145
  %5 = bitcast i8* %4 to i64*, !dbg !146
  store i64* %5, i64** %src, align 8, !dbg !144
  call void @llvm.dbg.declare(metadata i64** %end, metadata !147, metadata !41), !dbg !148
  %6 = load i64*, i64** %src, align 8, !dbg !149
  %7 = bitcast i64* %6 to i8*, !dbg !150
  %8 = load i64, i64* %length.addr, align 8, !dbg !151
  %add.ptr = getelementptr inbounds i8, i8* %7, i64 %8, !dbg !152
  %9 = bitcast i8* %add.ptr to i64*, !dbg !153
  store i64* %9, i64** %end, align 8, !dbg !148
  call void @llvm.dbg.declare(metadata i64** %dst, metadata !154, metadata !41), !dbg !155
  %10 = load i8*, i8** %to.addr, align 8, !dbg !156
  %11 = load i32, i32* %index.addr, align 4, !dbg !157
  %idx.ext = sext i32 %11 to i64, !dbg !158
  %add.ptr8 = getelementptr inbounds i8, i8* %10, i64 %idx.ext, !dbg !158
  %12 = bitcast i8* %add.ptr8 to i64*, !dbg !159
  store i64* %12, i64** %dst, align 8, !dbg !155
  br label %while.cond, !dbg !160

while.cond:                                       ; preds = %while.body, %if.then
  %13 = load i64*, i64** %src, align 8, !dbg !161
  %14 = load i64*, i64** %end, align 8, !dbg !163
  %cmp9 = icmp ult i64* %13, %14, !dbg !164
  br i1 %cmp9, label %while.body, label %while.end, !dbg !165

while.body:                                       ; preds = %while.cond
  %15 = load i64*, i64** %src, align 8, !dbg !166
  %incdec.ptr = getelementptr inbounds i64, i64* %15, i32 1, !dbg !166
  store i64* %incdec.ptr, i64** %src, align 8, !dbg !166
  %16 = load i64, i64* %15, align 8, !dbg !166
  %17 = call i64 @llvm.bswap.i64(i64 %16), !dbg !166
  %18 = load i64*, i64** %dst, align 8, !dbg !168
  %incdec.ptr11 = getelementptr inbounds i64, i64* %18, i32 1, !dbg !168
  store i64* %incdec.ptr11, i64** %dst, align 8, !dbg !168
  store i64 %17, i64* %18, align 8, !dbg !169
  br label %while.cond, !dbg !170

while.end:                                        ; preds = %while.cond
  br label %if.end, !dbg !171

if.else:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i8** %src12, metadata !172, metadata !41), !dbg !174
  %19 = load i8*, i8** %from.addr, align 8, !dbg !175
  store i8* %19, i8** %src12, align 8, !dbg !174
  %20 = load i32, i32* %index.addr, align 4, !dbg !176
  %conv13 = sext i32 %20 to i64, !dbg !176
  %21 = load i64, i64* %length.addr, align 8, !dbg !178
  %add = add i64 %21, %conv13, !dbg !178
  store i64 %add, i64* %length.addr, align 8, !dbg !178
  br label %for.cond, !dbg !179

for.cond:                                         ; preds = %for.inc, %if.else
  %22 = load i32, i32* %index.addr, align 4, !dbg !180
  %conv14 = sext i32 %22 to i64, !dbg !183
  %23 = load i64, i64* %length.addr, align 8, !dbg !184
  %cmp15 = icmp ult i64 %conv14, %23, !dbg !185
  br i1 %cmp15, label %for.body, label %for.end, !dbg !186

for.body:                                         ; preds = %for.cond
  %24 = load i8*, i8** %src12, align 8, !dbg !187
  %incdec.ptr17 = getelementptr inbounds i8, i8* %24, i32 1, !dbg !187
  store i8* %incdec.ptr17, i8** %src12, align 8, !dbg !187
  %25 = load i8, i8* %24, align 1, !dbg !189
  %26 = load i32, i32* %index.addr, align 4, !dbg !190
  %xor = xor i32 %26, 7, !dbg !191
  %idxprom = sext i32 %xor to i64, !dbg !192
  %27 = load i8*, i8** %to.addr, align 8, !dbg !193
  %arrayidx = getelementptr inbounds i8, i8* %27, i64 %idxprom, !dbg !192
  store i8 %25, i8* %arrayidx, align 1, !dbg !194
  br label %for.inc, !dbg !192

for.inc:                                          ; preds = %for.body
  %28 = load i32, i32* %index.addr, align 4, !dbg !195
  %inc = add nsw i32 %28, 1, !dbg !195
  store i32 %inc, i32* %index.addr, align 4, !dbg !195
  br label %for.cond, !dbg !197

for.end:                                          ; preds = %for.cond
  br label %if.end

if.end:                                           ; preds = %for.end, %while.end
  ret void, !dbg !198
}

; Function Attrs: nounwind readnone
declare i64 @llvm.bswap.i64(i64) #1

; Function Attrs: nounwind uwtable
define void @rhash_swap_copy_u64_to_str(i8* %to, i8* %from, i64 %length) #0 !dbg !30 {
entry:
  %to.addr = alloca i8*, align 8
  %from.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %src = alloca i64*, align 8
  %end = alloca i64*, align 8
  %dst = alloca i64*, align 8
  %index = alloca i64, align 8
  %dst9 = alloca i8*, align 8
  store i8* %to, i8** %to.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %to.addr, metadata !199, metadata !41), !dbg !200
  store i8* %from, i8** %from.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %from.addr, metadata !201, metadata !41), !dbg !202
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !203, metadata !41), !dbg !204
  %0 = load i8*, i8** %to.addr, align 8, !dbg !205
  %sub.ptr.lhs.cast = ptrtoint i8* %0 to i64, !dbg !207
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, 0, !dbg !207
  %conv = trunc i64 %sub.ptr.sub to i32, !dbg !208
  %conv1 = sext i32 %conv to i64, !dbg !208
  %1 = load i8*, i8** %from.addr, align 8, !dbg !209
  %sub.ptr.lhs.cast2 = ptrtoint i8* %1 to i64, !dbg !210
  %sub.ptr.sub3 = sub i64 %sub.ptr.lhs.cast2, 0, !dbg !210
  %or = or i64 %conv1, %sub.ptr.sub3, !dbg !211
  %2 = load i64, i64* %length.addr, align 8, !dbg !212
  %or4 = or i64 %or, %2, !dbg !213
  %and = and i64 %or4, 7, !dbg !214
  %cmp = icmp eq i64 0, %and, !dbg !215
  br i1 %cmp, label %if.then, label %if.else, !dbg !216

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i64** %src, metadata !217, metadata !41), !dbg !219
  %3 = load i8*, i8** %from.addr, align 8, !dbg !220
  %4 = bitcast i8* %3 to i64*, !dbg !221
  store i64* %4, i64** %src, align 8, !dbg !219
  call void @llvm.dbg.declare(metadata i64** %end, metadata !222, metadata !41), !dbg !223
  %5 = load i64*, i64** %src, align 8, !dbg !224
  %6 = bitcast i64* %5 to i8*, !dbg !225
  %7 = load i64, i64* %length.addr, align 8, !dbg !226
  %add.ptr = getelementptr inbounds i8, i8* %6, i64 %7, !dbg !227
  %8 = bitcast i8* %add.ptr to i64*, !dbg !228
  store i64* %8, i64** %end, align 8, !dbg !223
  call void @llvm.dbg.declare(metadata i64** %dst, metadata !229, metadata !41), !dbg !230
  %9 = load i8*, i8** %to.addr, align 8, !dbg !231
  %10 = bitcast i8* %9 to i64*, !dbg !232
  store i64* %10, i64** %dst, align 8, !dbg !230
  br label %while.cond, !dbg !233

while.cond:                                       ; preds = %while.body, %if.then
  %11 = load i64*, i64** %src, align 8, !dbg !234
  %12 = load i64*, i64** %end, align 8, !dbg !236
  %cmp6 = icmp ult i64* %11, %12, !dbg !237
  br i1 %cmp6, label %while.body, label %while.end, !dbg !238

while.body:                                       ; preds = %while.cond
  %13 = load i64*, i64** %src, align 8, !dbg !239
  %incdec.ptr = getelementptr inbounds i64, i64* %13, i32 1, !dbg !239
  store i64* %incdec.ptr, i64** %src, align 8, !dbg !239
  %14 = load i64, i64* %13, align 8, !dbg !239
  %15 = call i64 @llvm.bswap.i64(i64 %14), !dbg !239
  %16 = load i64*, i64** %dst, align 8, !dbg !241
  %incdec.ptr8 = getelementptr inbounds i64, i64* %16, i32 1, !dbg !241
  store i64* %incdec.ptr8, i64** %dst, align 8, !dbg !241
  store i64 %15, i64* %16, align 8, !dbg !242
  br label %while.cond, !dbg !243

while.end:                                        ; preds = %while.cond
  br label %if.end, !dbg !244

if.else:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i64* %index, metadata !245, metadata !41), !dbg !247
  call void @llvm.dbg.declare(metadata i8** %dst9, metadata !248, metadata !41), !dbg !249
  %17 = load i8*, i8** %to.addr, align 8, !dbg !250
  store i8* %17, i8** %dst9, align 8, !dbg !249
  store i64 0, i64* %index, align 8, !dbg !251
  br label %for.cond, !dbg !253

for.cond:                                         ; preds = %for.inc, %if.else
  %18 = load i64, i64* %index, align 8, !dbg !254
  %19 = load i64, i64* %length.addr, align 8, !dbg !257
  %cmp10 = icmp ult i64 %18, %19, !dbg !258
  br i1 %cmp10, label %for.body, label %for.end, !dbg !259

for.body:                                         ; preds = %for.cond
  %20 = load i64, i64* %index, align 8, !dbg !260
  %xor = xor i64 %20, 7, !dbg !262
  %21 = load i8*, i8** %from.addr, align 8, !dbg !263
  %arrayidx = getelementptr inbounds i8, i8* %21, i64 %xor, !dbg !264
  %22 = load i8, i8* %arrayidx, align 1, !dbg !264
  %23 = load i8*, i8** %dst9, align 8, !dbg !265
  %incdec.ptr12 = getelementptr inbounds i8, i8* %23, i32 1, !dbg !265
  store i8* %incdec.ptr12, i8** %dst9, align 8, !dbg !265
  store i8 %22, i8* %23, align 1, !dbg !266
  br label %for.inc, !dbg !267

for.inc:                                          ; preds = %for.body
  %24 = load i64, i64* %index, align 8, !dbg !268
  %inc = add i64 %24, 1, !dbg !268
  store i64 %inc, i64* %index, align 8, !dbg !268
  br label %for.cond, !dbg !270

for.end:                                          ; preds = %for.cond
  br label %if.end

if.end:                                           ; preds = %for.end, %while.end
  ret void, !dbg !271
}

; Function Attrs: nounwind uwtable
define void @rhash_u32_mem_swap(i32* %arr, i32 %length) #0 !dbg !33 {
entry:
  %arr.addr = alloca i32*, align 8
  %length.addr = alloca i32, align 4
  %end = alloca i32*, align 8
  store i32* %arr, i32** %arr.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %arr.addr, metadata !272, metadata !41), !dbg !273
  store i32 %length, i32* %length.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %length.addr, metadata !274, metadata !41), !dbg !275
  call void @llvm.dbg.declare(metadata i32** %end, metadata !276, metadata !41), !dbg !277
  %0 = load i32*, i32** %arr.addr, align 8, !dbg !278
  %1 = load i32, i32* %length.addr, align 4, !dbg !279
  %idx.ext = sext i32 %1 to i64, !dbg !280
  %add.ptr = getelementptr inbounds i32, i32* %0, i64 %idx.ext, !dbg !280
  store i32* %add.ptr, i32** %end, align 8, !dbg !277
  br label %for.cond, !dbg !281

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load i32*, i32** %arr.addr, align 8, !dbg !282
  %3 = load i32*, i32** %end, align 8, !dbg !286
  %cmp = icmp ult i32* %2, %3, !dbg !287
  br i1 %cmp, label %for.body, label %for.end, !dbg !288

for.body:                                         ; preds = %for.cond
  %4 = load i32*, i32** %arr.addr, align 8, !dbg !289
  %5 = load i32, i32* %4, align 4, !dbg !289
  %6 = call i32 @llvm.bswap.i32(i32 %5), !dbg !289
  %7 = load i32*, i32** %arr.addr, align 8, !dbg !291
  store i32 %6, i32* %7, align 4, !dbg !292
  br label %for.inc, !dbg !293

for.inc:                                          ; preds = %for.body
  %8 = load i32*, i32** %arr.addr, align 8, !dbg !294
  %incdec.ptr = getelementptr inbounds i32, i32* %8, i32 1, !dbg !294
  store i32* %incdec.ptr, i32** %arr.addr, align 8, !dbg !294
  br label %for.cond, !dbg !296

for.end:                                          ; preds = %for.cond
  ret void, !dbg !297
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!37, !38}
!llvm.ident = !{!39}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !22)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/byte_order.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!2 = !{}
!3 = !{!4, !5, !7, !12, !14, !15, !18, !21}
!4 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64, align: 64)
!8 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !9)
!9 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !10, line: 51, baseType: !11)
!10 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!11 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64, align: 64)
!13 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !6)
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!15 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !16, line: 62, baseType: !17)
!16 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!17 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!19 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !20)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !10, line: 55, baseType: !17)
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64, align: 64)
!22 = !{!23, !29, !30, !33}
!23 = distinct !DISubprogram(name: "rhash_swap_copy_str_to_u32", scope: !1, file: !1, line: 74, type: !24, isLocal: false, isDefinition: true, scopeLine: 75, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!24 = !DISubroutineType(types: !25)
!25 = !{null, !26, !4, !27, !15}
!26 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!29 = distinct !DISubprogram(name: "rhash_swap_copy_str_to_u64", scope: !1, file: !1, line: 99, type: !24, isLocal: false, isDefinition: true, scopeLine: 100, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!30 = distinct !DISubprogram(name: "rhash_swap_copy_u64_to_str", scope: !1, file: !1, line: 122, type: !31, isLocal: false, isDefinition: true, scopeLine: 123, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!31 = !DISubroutineType(types: !32)
!32 = !{null, !26, !27, !15}
!33 = distinct !DISubprogram(name: "rhash_u32_mem_swap", scope: !1, file: !1, line: 144, type: !34, isLocal: false, isDefinition: true, scopeLine: 145, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!34 = !DISubroutineType(types: !35)
!35 = !{null, !36, !4}
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!37 = !{i32 2, !"Dwarf Version", i32 4}
!38 = !{i32 2, !"Debug Info Version", i32 3}
!39 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!40 = !DILocalVariable(name: "to", arg: 1, scope: !23, file: !1, line: 74, type: !26)
!41 = !DIExpression()
!42 = !DILocation(line: 74, column: 39, scope: !23)
!43 = !DILocalVariable(name: "index", arg: 2, scope: !23, file: !1, line: 74, type: !4)
!44 = !DILocation(line: 74, column: 47, scope: !23)
!45 = !DILocalVariable(name: "from", arg: 3, scope: !23, file: !1, line: 74, type: !27)
!46 = !DILocation(line: 74, column: 66, scope: !23)
!47 = !DILocalVariable(name: "length", arg: 4, scope: !23, file: !1, line: 74, type: !15)
!48 = !DILocation(line: 74, column: 79, scope: !23)
!49 = !DILocation(line: 77, column: 28, scope: !50)
!50 = distinct !DILexicalBlock(scope: !23, file: !1, line: 77, column: 7)
!51 = !DILocation(line: 77, column: 31, scope: !50)
!52 = !DILocation(line: 77, column: 15, scope: !50)
!53 = !DILocation(line: 77, column: 53, scope: !50)
!54 = !DILocation(line: 77, column: 58, scope: !50)
!55 = !DILocation(line: 77, column: 43, scope: !50)
!56 = !DILocation(line: 77, column: 72, scope: !50)
!57 = !DILocation(line: 77, column: 70, scope: !50)
!58 = !DILocation(line: 77, column: 80, scope: !50)
!59 = !DILocation(line: 77, column: 78, scope: !50)
!60 = !DILocation(line: 77, column: 89, scope: !50)
!61 = !DILocation(line: 77, column: 9, scope: !50)
!62 = !DILocation(line: 77, column: 7, scope: !23)
!63 = !DILocalVariable(name: "src", scope: !64, file: !1, line: 79, type: !7)
!64 = distinct !DILexicalBlock(scope: !50, file: !1, line: 77, column: 96)
!65 = !DILocation(line: 79, column: 19, scope: !64)
!66 = !DILocation(line: 79, column: 42, scope: !64)
!67 = !DILocation(line: 79, column: 25, scope: !64)
!68 = !DILocalVariable(name: "end", scope: !64, file: !1, line: 80, type: !7)
!69 = !DILocation(line: 80, column: 19, scope: !64)
!70 = !DILocation(line: 80, column: 56, scope: !64)
!71 = !DILocation(line: 80, column: 43, scope: !64)
!72 = !DILocation(line: 80, column: 62, scope: !64)
!73 = !DILocation(line: 80, column: 60, scope: !64)
!74 = !DILocation(line: 80, column: 25, scope: !64)
!75 = !DILocalVariable(name: "dst", scope: !64, file: !1, line: 81, type: !14)
!76 = !DILocation(line: 81, column: 13, scope: !64)
!77 = !DILocation(line: 81, column: 38, scope: !64)
!78 = !DILocation(line: 81, column: 43, scope: !64)
!79 = !DILocation(line: 81, column: 41, scope: !64)
!80 = !DILocation(line: 81, column: 19, scope: !64)
!81 = !DILocation(line: 82, column: 3, scope: !64)
!82 = !DILocation(line: 82, column: 10, scope: !83)
!83 = !DILexicalBlockFile(scope: !64, file: !1, discriminator: 1)
!84 = !DILocation(line: 82, column: 16, scope: !83)
!85 = !DILocation(line: 82, column: 14, scope: !83)
!86 = !DILocation(line: 82, column: 3, scope: !83)
!87 = !DILocation(line: 82, column: 32, scope: !88)
!88 = !DILexicalBlockFile(scope: !64, file: !1, discriminator: 2)
!89 = !DILocation(line: 82, column: 26, scope: !88)
!90 = !DILocation(line: 82, column: 30, scope: !88)
!91 = !DILocation(line: 82, column: 3, scope: !88)
!92 = !DILocation(line: 83, column: 2, scope: !64)
!93 = !DILocalVariable(name: "src", scope: !94, file: !1, line: 84, type: !12)
!94 = distinct !DILexicalBlock(scope: !50, file: !1, line: 83, column: 9)
!95 = !DILocation(line: 84, column: 15, scope: !94)
!96 = !DILocation(line: 84, column: 34, scope: !94)
!97 = !DILocation(line: 85, column: 18, scope: !98)
!98 = distinct !DILexicalBlock(scope: !94, file: !1, line: 85, column: 3)
!99 = !DILocation(line: 85, column: 15, scope: !98)
!100 = !DILocation(line: 85, column: 8, scope: !98)
!101 = !DILocation(line: 85, column: 33, scope: !102)
!102 = !DILexicalBlockFile(scope: !103, file: !1, discriminator: 1)
!103 = distinct !DILexicalBlock(scope: !98, file: !1, line: 85, column: 3)
!104 = !DILocation(line: 85, column: 25, scope: !102)
!105 = !DILocation(line: 85, column: 41, scope: !102)
!106 = !DILocation(line: 85, column: 39, scope: !102)
!107 = !DILocation(line: 85, column: 3, scope: !102)
!108 = !DILocation(line: 85, column: 88, scope: !109)
!109 = !DILexicalBlockFile(scope: !103, file: !1, discriminator: 2)
!110 = !DILocation(line: 85, column: 83, scope: !109)
!111 = !DILocation(line: 85, column: 70, scope: !109)
!112 = !DILocation(line: 85, column: 76, scope: !109)
!113 = !DILocation(line: 85, column: 58, scope: !109)
!114 = !DILocation(line: 85, column: 66, scope: !109)
!115 = !DILocation(line: 85, column: 81, scope: !109)
!116 = !DILocation(line: 85, column: 54, scope: !117)
!117 = !DILexicalBlockFile(scope: !103, file: !1, discriminator: 3)
!118 = !DILocation(line: 85, column: 3, scope: !117)
!119 = !DILocation(line: 87, column: 1, scope: !23)
!120 = !DILocalVariable(name: "to", arg: 1, scope: !29, file: !1, line: 99, type: !26)
!121 = !DILocation(line: 99, column: 39, scope: !29)
!122 = !DILocalVariable(name: "index", arg: 2, scope: !29, file: !1, line: 99, type: !4)
!123 = !DILocation(line: 99, column: 47, scope: !29)
!124 = !DILocalVariable(name: "from", arg: 3, scope: !29, file: !1, line: 99, type: !27)
!125 = !DILocation(line: 99, column: 66, scope: !29)
!126 = !DILocalVariable(name: "length", arg: 4, scope: !29, file: !1, line: 99, type: !15)
!127 = !DILocation(line: 99, column: 79, scope: !29)
!128 = !DILocation(line: 102, column: 28, scope: !129)
!129 = distinct !DILexicalBlock(scope: !29, file: !1, line: 102, column: 7)
!130 = !DILocation(line: 102, column: 31, scope: !129)
!131 = !DILocation(line: 102, column: 15, scope: !129)
!132 = !DILocation(line: 102, column: 53, scope: !129)
!133 = !DILocation(line: 102, column: 58, scope: !129)
!134 = !DILocation(line: 102, column: 43, scope: !129)
!135 = !DILocation(line: 102, column: 72, scope: !129)
!136 = !DILocation(line: 102, column: 70, scope: !129)
!137 = !DILocation(line: 102, column: 80, scope: !129)
!138 = !DILocation(line: 102, column: 78, scope: !129)
!139 = !DILocation(line: 102, column: 89, scope: !129)
!140 = !DILocation(line: 102, column: 9, scope: !129)
!141 = !DILocation(line: 102, column: 7, scope: !29)
!142 = !DILocalVariable(name: "src", scope: !143, file: !1, line: 104, type: !18)
!143 = distinct !DILexicalBlock(scope: !129, file: !1, line: 102, column: 96)
!144 = !DILocation(line: 104, column: 19, scope: !143)
!145 = !DILocation(line: 104, column: 42, scope: !143)
!146 = !DILocation(line: 104, column: 25, scope: !143)
!147 = !DILocalVariable(name: "end", scope: !143, file: !1, line: 105, type: !18)
!148 = !DILocation(line: 105, column: 19, scope: !143)
!149 = !DILocation(line: 105, column: 56, scope: !143)
!150 = !DILocation(line: 105, column: 43, scope: !143)
!151 = !DILocation(line: 105, column: 62, scope: !143)
!152 = !DILocation(line: 105, column: 60, scope: !143)
!153 = !DILocation(line: 105, column: 25, scope: !143)
!154 = !DILocalVariable(name: "dst", scope: !143, file: !1, line: 106, type: !21)
!155 = !DILocation(line: 106, column: 13, scope: !143)
!156 = !DILocation(line: 106, column: 38, scope: !143)
!157 = !DILocation(line: 106, column: 43, scope: !143)
!158 = !DILocation(line: 106, column: 41, scope: !143)
!159 = !DILocation(line: 106, column: 19, scope: !143)
!160 = !DILocation(line: 107, column: 3, scope: !143)
!161 = !DILocation(line: 107, column: 10, scope: !162)
!162 = !DILexicalBlockFile(scope: !143, file: !1, discriminator: 1)
!163 = !DILocation(line: 107, column: 16, scope: !162)
!164 = !DILocation(line: 107, column: 14, scope: !162)
!165 = !DILocation(line: 107, column: 3, scope: !162)
!166 = !DILocation(line: 107, column: 32, scope: !167)
!167 = !DILexicalBlockFile(scope: !143, file: !1, discriminator: 2)
!168 = !DILocation(line: 107, column: 26, scope: !167)
!169 = !DILocation(line: 107, column: 30, scope: !167)
!170 = !DILocation(line: 107, column: 3, scope: !167)
!171 = !DILocation(line: 108, column: 2, scope: !143)
!172 = !DILocalVariable(name: "src", scope: !173, file: !1, line: 109, type: !12)
!173 = distinct !DILexicalBlock(scope: !129, file: !1, line: 108, column: 9)
!174 = !DILocation(line: 109, column: 15, scope: !173)
!175 = !DILocation(line: 109, column: 34, scope: !173)
!176 = !DILocation(line: 110, column: 18, scope: !177)
!177 = distinct !DILexicalBlock(scope: !173, file: !1, line: 110, column: 3)
!178 = !DILocation(line: 110, column: 15, scope: !177)
!179 = !DILocation(line: 110, column: 8, scope: !177)
!180 = !DILocation(line: 110, column: 33, scope: !181)
!181 = !DILexicalBlockFile(scope: !182, file: !1, discriminator: 1)
!182 = distinct !DILexicalBlock(scope: !177, file: !1, line: 110, column: 3)
!183 = !DILocation(line: 110, column: 25, scope: !181)
!184 = !DILocation(line: 110, column: 41, scope: !181)
!185 = !DILocation(line: 110, column: 39, scope: !181)
!186 = !DILocation(line: 110, column: 3, scope: !181)
!187 = !DILocation(line: 110, column: 88, scope: !188)
!188 = !DILexicalBlockFile(scope: !182, file: !1, discriminator: 2)
!189 = !DILocation(line: 110, column: 83, scope: !188)
!190 = !DILocation(line: 110, column: 70, scope: !188)
!191 = !DILocation(line: 110, column: 76, scope: !188)
!192 = !DILocation(line: 110, column: 58, scope: !188)
!193 = !DILocation(line: 110, column: 66, scope: !188)
!194 = !DILocation(line: 110, column: 81, scope: !188)
!195 = !DILocation(line: 110, column: 54, scope: !196)
!196 = !DILexicalBlockFile(scope: !182, file: !1, discriminator: 3)
!197 = !DILocation(line: 110, column: 3, scope: !196)
!198 = !DILocation(line: 112, column: 1, scope: !29)
!199 = !DILocalVariable(name: "to", arg: 1, scope: !30, file: !1, line: 122, type: !26)
!200 = !DILocation(line: 122, column: 39, scope: !30)
!201 = !DILocalVariable(name: "from", arg: 2, scope: !30, file: !1, line: 122, type: !27)
!202 = !DILocation(line: 122, column: 55, scope: !30)
!203 = !DILocalVariable(name: "length", arg: 3, scope: !30, file: !1, line: 122, type: !15)
!204 = !DILocation(line: 122, column: 68, scope: !30)
!205 = !DILocation(line: 125, column: 28, scope: !206)
!206 = distinct !DILexicalBlock(scope: !30, file: !1, line: 125, column: 7)
!207 = !DILocation(line: 125, column: 31, scope: !206)
!208 = !DILocation(line: 125, column: 15, scope: !206)
!209 = !DILocation(line: 125, column: 53, scope: !206)
!210 = !DILocation(line: 125, column: 58, scope: !206)
!211 = !DILocation(line: 125, column: 43, scope: !206)
!212 = !DILocation(line: 125, column: 72, scope: !206)
!213 = !DILocation(line: 125, column: 70, scope: !206)
!214 = !DILocation(line: 125, column: 81, scope: !206)
!215 = !DILocation(line: 125, column: 9, scope: !206)
!216 = !DILocation(line: 125, column: 7, scope: !30)
!217 = !DILocalVariable(name: "src", scope: !218, file: !1, line: 127, type: !18)
!218 = distinct !DILexicalBlock(scope: !206, file: !1, line: 125, column: 88)
!219 = !DILocation(line: 127, column: 19, scope: !218)
!220 = !DILocation(line: 127, column: 42, scope: !218)
!221 = !DILocation(line: 127, column: 25, scope: !218)
!222 = !DILocalVariable(name: "end", scope: !218, file: !1, line: 128, type: !18)
!223 = !DILocation(line: 128, column: 19, scope: !218)
!224 = !DILocation(line: 128, column: 56, scope: !218)
!225 = !DILocation(line: 128, column: 43, scope: !218)
!226 = !DILocation(line: 128, column: 62, scope: !218)
!227 = !DILocation(line: 128, column: 60, scope: !218)
!228 = !DILocation(line: 128, column: 25, scope: !218)
!229 = !DILocalVariable(name: "dst", scope: !218, file: !1, line: 129, type: !21)
!230 = !DILocation(line: 129, column: 13, scope: !218)
!231 = !DILocation(line: 129, column: 30, scope: !218)
!232 = !DILocation(line: 129, column: 19, scope: !218)
!233 = !DILocation(line: 130, column: 3, scope: !218)
!234 = !DILocation(line: 130, column: 10, scope: !235)
!235 = !DILexicalBlockFile(scope: !218, file: !1, discriminator: 1)
!236 = !DILocation(line: 130, column: 16, scope: !235)
!237 = !DILocation(line: 130, column: 14, scope: !235)
!238 = !DILocation(line: 130, column: 3, scope: !235)
!239 = !DILocation(line: 130, column: 32, scope: !240)
!240 = !DILexicalBlockFile(scope: !218, file: !1, discriminator: 2)
!241 = !DILocation(line: 130, column: 26, scope: !240)
!242 = !DILocation(line: 130, column: 30, scope: !240)
!243 = !DILocation(line: 130, column: 3, scope: !240)
!244 = !DILocation(line: 131, column: 2, scope: !218)
!245 = !DILocalVariable(name: "index", scope: !246, file: !1, line: 132, type: !15)
!246 = distinct !DILexicalBlock(scope: !206, file: !1, line: 131, column: 9)
!247 = !DILocation(line: 132, column: 10, scope: !246)
!248 = !DILocalVariable(name: "dst", scope: !246, file: !1, line: 133, type: !5)
!249 = !DILocation(line: 133, column: 9, scope: !246)
!250 = !DILocation(line: 133, column: 22, scope: !246)
!251 = !DILocation(line: 134, column: 14, scope: !252)
!252 = distinct !DILexicalBlock(scope: !246, file: !1, line: 134, column: 3)
!253 = !DILocation(line: 134, column: 8, scope: !252)
!254 = !DILocation(line: 134, column: 19, scope: !255)
!255 = !DILexicalBlockFile(scope: !256, file: !1, discriminator: 1)
!256 = distinct !DILexicalBlock(scope: !252, file: !1, line: 134, column: 3)
!257 = !DILocation(line: 134, column: 27, scope: !255)
!258 = !DILocation(line: 134, column: 25, scope: !255)
!259 = !DILocation(line: 134, column: 3, scope: !255)
!260 = !DILocation(line: 134, column: 69, scope: !261)
!261 = !DILexicalBlockFile(scope: !256, file: !1, discriminator: 2)
!262 = !DILocation(line: 134, column: 75, scope: !261)
!263 = !DILocation(line: 134, column: 63, scope: !261)
!264 = !DILocation(line: 134, column: 55, scope: !261)
!265 = !DILocation(line: 134, column: 49, scope: !261)
!266 = !DILocation(line: 134, column: 53, scope: !261)
!267 = !DILocation(line: 134, column: 44, scope: !261)
!268 = !DILocation(line: 134, column: 40, scope: !269)
!269 = !DILexicalBlockFile(scope: !256, file: !1, discriminator: 3)
!270 = !DILocation(line: 134, column: 3, scope: !269)
!271 = !DILocation(line: 136, column: 1, scope: !30)
!272 = !DILocalVariable(name: "arr", arg: 1, scope: !33, file: !1, line: 144, type: !36)
!273 = !DILocation(line: 144, column: 35, scope: !33)
!274 = !DILocalVariable(name: "length", arg: 2, scope: !33, file: !1, line: 144, type: !4)
!275 = !DILocation(line: 144, column: 44, scope: !33)
!276 = !DILocalVariable(name: "end", scope: !33, file: !1, line: 146, type: !36)
!277 = !DILocation(line: 146, column: 12, scope: !33)
!278 = !DILocation(line: 146, column: 18, scope: !33)
!279 = !DILocation(line: 146, column: 24, scope: !33)
!280 = !DILocation(line: 146, column: 22, scope: !33)
!281 = !DILocation(line: 147, column: 2, scope: !33)
!282 = !DILocation(line: 147, column: 9, scope: !283)
!283 = !DILexicalBlockFile(scope: !284, file: !1, discriminator: 1)
!284 = distinct !DILexicalBlock(scope: !285, file: !1, line: 147, column: 2)
!285 = distinct !DILexicalBlock(scope: !33, file: !1, line: 147, column: 2)
!286 = !DILocation(line: 147, column: 15, scope: !283)
!287 = !DILocation(line: 147, column: 13, scope: !283)
!288 = !DILocation(line: 147, column: 2, scope: !283)
!289 = !DILocation(line: 148, column: 10, scope: !290)
!290 = distinct !DILexicalBlock(scope: !284, file: !1, line: 147, column: 27)
!291 = !DILocation(line: 148, column: 4, scope: !290)
!292 = !DILocation(line: 148, column: 8, scope: !290)
!293 = !DILocation(line: 149, column: 2, scope: !290)
!294 = !DILocation(line: 147, column: 23, scope: !295)
!295 = !DILexicalBlockFile(scope: !284, file: !1, discriminator: 2)
!296 = !DILocation(line: 147, column: 2, scope: !295)
!297 = !DILocation(line: 150, column: 1, scope: !33)
