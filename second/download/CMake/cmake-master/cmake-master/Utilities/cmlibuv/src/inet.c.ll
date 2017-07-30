; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/inet.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i32, i32 }

@inet_ntop4.fmt = internal constant [12 x i8] c"%u.%u.%u.%u\00", align 1
@.str = private unnamed_addr constant [3 x i8] c"%x\00", align 1
@inet_pton4.digits = internal constant [11 x i8] c"0123456789\00", align 1
@inet_pton6.xdigits_l = internal constant [17 x i8] c"0123456789abcdef\00", align 16
@inet_pton6.xdigits_u = internal constant [17 x i8] c"0123456789ABCDEF\00", align 16

; Function Attrs: nounwind uwtable
define i32 @uv_inet_ntop(i32 %af, i8* %src, i8* %dst, i64 %size) #0 !dbg !93 {
entry:
  %retval = alloca i32, align 4
  %af.addr = alloca i32, align 4
  %src.addr = alloca i8*, align 8
  %dst.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  store i32 %af, i32* %af.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %af.addr, metadata !132, metadata !133), !dbg !134
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !135, metadata !133), !dbg !136
  store i8* %dst, i8** %dst.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dst.addr, metadata !137, metadata !133), !dbg !138
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !139, metadata !133), !dbg !140
  %0 = load i32, i32* %af.addr, align 4, !dbg !141
  switch i32 %0, label %sw.default [
    i32 2, label %sw.bb
    i32 10, label %sw.bb1
  ], !dbg !142

sw.bb:                                            ; preds = %entry
  %1 = load i8*, i8** %src.addr, align 8, !dbg !143
  %2 = load i8*, i8** %dst.addr, align 8, !dbg !145
  %3 = load i64, i64* %size.addr, align 8, !dbg !146
  %call = call i32 @inet_ntop4(i8* %1, i8* %2, i64 %3), !dbg !147
  store i32 %call, i32* %retval, align 4, !dbg !148
  br label %return, !dbg !148

sw.bb1:                                           ; preds = %entry
  %4 = load i8*, i8** %src.addr, align 8, !dbg !149
  %5 = load i8*, i8** %dst.addr, align 8, !dbg !150
  %6 = load i64, i64* %size.addr, align 8, !dbg !151
  %call2 = call i32 @inet_ntop6(i8* %4, i8* %5, i64 %6), !dbg !152
  store i32 %call2, i32* %retval, align 4, !dbg !153
  br label %return, !dbg !153

sw.default:                                       ; preds = %entry
  store i32 -97, i32* %retval, align 4, !dbg !154
  br label %return, !dbg !154

return:                                           ; preds = %sw.default, %sw.bb1, %sw.bb
  %7 = load i32, i32* %retval, align 4, !dbg !155
  ret i32 %7, !dbg !155
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i32 @inet_ntop4(i8* %src, i8* %dst, i64 %size) #0 !dbg !104 {
entry:
  %retval = alloca i32, align 4
  %src.addr = alloca i8*, align 8
  %dst.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %tmp = alloca [16 x i8], align 16
  %l = alloca i32, align 4
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !156, metadata !133), !dbg !157
  store i8* %dst, i8** %dst.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dst.addr, metadata !158, metadata !133), !dbg !159
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !160, metadata !133), !dbg !161
  call void @llvm.dbg.declare(metadata [16 x i8]* %tmp, metadata !162, metadata !133), !dbg !166
  call void @llvm.dbg.declare(metadata i32* %l, metadata !167, metadata !133), !dbg !168
  %arraydecay = getelementptr inbounds [16 x i8], [16 x i8]* %tmp, i32 0, i32 0, !dbg !169
  %0 = load i8*, i8** %src.addr, align 8, !dbg !170
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !170
  %1 = load i8, i8* %arrayidx, align 1, !dbg !170
  %conv = zext i8 %1 to i32, !dbg !170
  %2 = load i8*, i8** %src.addr, align 8, !dbg !171
  %arrayidx2 = getelementptr inbounds i8, i8* %2, i64 1, !dbg !171
  %3 = load i8, i8* %arrayidx2, align 1, !dbg !171
  %conv3 = zext i8 %3 to i32, !dbg !171
  %4 = load i8*, i8** %src.addr, align 8, !dbg !172
  %arrayidx4 = getelementptr inbounds i8, i8* %4, i64 2, !dbg !172
  %5 = load i8, i8* %arrayidx4, align 1, !dbg !172
  %conv5 = zext i8 %5 to i32, !dbg !172
  %6 = load i8*, i8** %src.addr, align 8, !dbg !173
  %arrayidx6 = getelementptr inbounds i8, i8* %6, i64 3, !dbg !173
  %7 = load i8, i8* %arrayidx6, align 1, !dbg !173
  %conv7 = zext i8 %7 to i32, !dbg !173
  %call = call i32 (i8*, i64, i8*, ...) @snprintf(i8* %arraydecay, i64 16, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @inet_ntop4.fmt, i32 0, i32 0), i32 %conv, i32 %conv3, i32 %conv5, i32 %conv7) #5, !dbg !174
  store i32 %call, i32* %l, align 4, !dbg !175
  %8 = load i32, i32* %l, align 4, !dbg !176
  %cmp = icmp sle i32 %8, 0, !dbg !178
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !179

lor.lhs.false:                                    ; preds = %entry
  %9 = load i32, i32* %l, align 4, !dbg !180
  %conv9 = sext i32 %9 to i64, !dbg !182
  %10 = load i64, i64* %size.addr, align 8, !dbg !183
  %cmp10 = icmp uge i64 %conv9, %10, !dbg !184
  br i1 %cmp10, label %if.then, label %if.end, !dbg !185

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -28, i32* %retval, align 4, !dbg !186
  br label %return, !dbg !186

if.end:                                           ; preds = %lor.lhs.false
  %11 = load i8*, i8** %dst.addr, align 8, !dbg !188
  %arraydecay12 = getelementptr inbounds [16 x i8], [16 x i8]* %tmp, i32 0, i32 0, !dbg !189
  %12 = load i64, i64* %size.addr, align 8, !dbg !190
  %call13 = call i8* @strncpy(i8* %11, i8* %arraydecay12, i64 %12) #5, !dbg !191
  %13 = load i64, i64* %size.addr, align 8, !dbg !192
  %sub = sub i64 %13, 1, !dbg !193
  %14 = load i8*, i8** %dst.addr, align 8, !dbg !194
  %arrayidx14 = getelementptr inbounds i8, i8* %14, i64 %sub, !dbg !194
  store i8 0, i8* %arrayidx14, align 1, !dbg !195
  store i32 0, i32* %retval, align 4, !dbg !196
  br label %return, !dbg !196

return:                                           ; preds = %if.end, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !197
  ret i32 %15, !dbg !197
}

; Function Attrs: nounwind uwtable
define internal i32 @inet_ntop6(i8* %src, i8* %dst, i64 %size) #0 !dbg !109 {
entry:
  %retval = alloca i32, align 4
  %src.addr = alloca i8*, align 8
  %dst.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %tmp = alloca [46 x i8], align 16
  %tp = alloca i8*, align 8
  %best = alloca %struct.anon, align 4
  %cur = alloca %struct.anon, align 4
  %words = alloca [8 x i32], align 16
  %i = alloca i32, align 4
  %err = alloca i32, align 4
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !198, metadata !133), !dbg !199
  store i8* %dst, i8** %dst.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dst.addr, metadata !200, metadata !133), !dbg !201
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !202, metadata !133), !dbg !203
  call void @llvm.dbg.declare(metadata [46 x i8]* %tmp, metadata !204, metadata !133), !dbg !208
  call void @llvm.dbg.declare(metadata i8** %tp, metadata !209, metadata !133), !dbg !210
  call void @llvm.dbg.declare(metadata %struct.anon* %best, metadata !211, metadata !133), !dbg !216
  call void @llvm.dbg.declare(metadata %struct.anon* %cur, metadata !217, metadata !133), !dbg !218
  call void @llvm.dbg.declare(metadata [8 x i32]* %words, metadata !219, metadata !133), !dbg !224
  call void @llvm.dbg.declare(metadata i32* %i, metadata !225, metadata !133), !dbg !226
  %arraydecay = getelementptr inbounds [8 x i32], [8 x i32]* %words, i32 0, i32 0, !dbg !227
  %0 = bitcast i32* %arraydecay to i8*, !dbg !227
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 32, i32 16, i1 false), !dbg !227
  store i32 0, i32* %i, align 4, !dbg !228
  br label %for.cond, !dbg !230

for.cond:                                         ; preds = %for.inc, %entry
  %1 = load i32, i32* %i, align 4, !dbg !231
  %cmp = icmp slt i32 %1, 16, !dbg !234
  br i1 %cmp, label %for.body, label %for.end, !dbg !235

for.body:                                         ; preds = %for.cond
  %2 = load i32, i32* %i, align 4, !dbg !236
  %idxprom = sext i32 %2 to i64, !dbg !237
  %3 = load i8*, i8** %src.addr, align 8, !dbg !237
  %arrayidx = getelementptr inbounds i8, i8* %3, i64 %idxprom, !dbg !237
  %4 = load i8, i8* %arrayidx, align 1, !dbg !237
  %conv = zext i8 %4 to i32, !dbg !237
  %5 = load i32, i32* %i, align 4, !dbg !238
  %rem = srem i32 %5, 2, !dbg !239
  %sub = sub nsw i32 1, %rem, !dbg !240
  %shl = shl i32 %sub, 3, !dbg !241
  %shl6 = shl i32 %conv, %shl, !dbg !242
  %6 = load i32, i32* %i, align 4, !dbg !243
  %div = sdiv i32 %6, 2, !dbg !244
  %idxprom7 = sext i32 %div to i64, !dbg !245
  %arrayidx8 = getelementptr inbounds [8 x i32], [8 x i32]* %words, i64 0, i64 %idxprom7, !dbg !245
  %7 = load i32, i32* %arrayidx8, align 4, !dbg !246
  %or = or i32 %7, %shl6, !dbg !246
  store i32 %or, i32* %arrayidx8, align 4, !dbg !246
  br label %for.inc, !dbg !245

for.inc:                                          ; preds = %for.body
  %8 = load i32, i32* %i, align 4, !dbg !247
  %inc = add nsw i32 %8, 1, !dbg !247
  store i32 %inc, i32* %i, align 4, !dbg !247
  br label %for.cond, !dbg !249

for.end:                                          ; preds = %for.cond
  %base = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 0, !dbg !250
  store i32 -1, i32* %base, align 4, !dbg !251
  %len = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 1, !dbg !252
  store i32 0, i32* %len, align 4, !dbg !253
  %base9 = getelementptr inbounds %struct.anon, %struct.anon* %cur, i32 0, i32 0, !dbg !254
  store i32 -1, i32* %base9, align 4, !dbg !255
  %len10 = getelementptr inbounds %struct.anon, %struct.anon* %cur, i32 0, i32 1, !dbg !256
  store i32 0, i32* %len10, align 4, !dbg !257
  store i32 0, i32* %i, align 4, !dbg !258
  br label %for.cond11, !dbg !260

for.cond11:                                       ; preds = %for.inc44, %for.end
  %9 = load i32, i32* %i, align 4, !dbg !261
  %cmp12 = icmp slt i32 %9, 8, !dbg !264
  br i1 %cmp12, label %for.body14, label %for.end46, !dbg !265

for.body14:                                       ; preds = %for.cond11
  %10 = load i32, i32* %i, align 4, !dbg !266
  %idxprom15 = sext i32 %10 to i64, !dbg !269
  %arrayidx16 = getelementptr inbounds [8 x i32], [8 x i32]* %words, i64 0, i64 %idxprom15, !dbg !269
  %11 = load i32, i32* %arrayidx16, align 4, !dbg !269
  %cmp17 = icmp eq i32 %11, 0, !dbg !270
  br i1 %cmp17, label %if.then, label %if.else27, !dbg !271

if.then:                                          ; preds = %for.body14
  %base19 = getelementptr inbounds %struct.anon, %struct.anon* %cur, i32 0, i32 0, !dbg !272
  %12 = load i32, i32* %base19, align 4, !dbg !272
  %cmp20 = icmp eq i32 %12, -1, !dbg !275
  br i1 %cmp20, label %if.then22, label %if.else, !dbg !276

if.then22:                                        ; preds = %if.then
  %13 = load i32, i32* %i, align 4, !dbg !277
  %base23 = getelementptr inbounds %struct.anon, %struct.anon* %cur, i32 0, i32 0, !dbg !278
  store i32 %13, i32* %base23, align 4, !dbg !279
  %len24 = getelementptr inbounds %struct.anon, %struct.anon* %cur, i32 0, i32 1, !dbg !280
  store i32 1, i32* %len24, align 4, !dbg !281
  br label %if.end, !dbg !282

if.else:                                          ; preds = %if.then
  %len25 = getelementptr inbounds %struct.anon, %struct.anon* %cur, i32 0, i32 1, !dbg !283
  %14 = load i32, i32* %len25, align 4, !dbg !284
  %inc26 = add nsw i32 %14, 1, !dbg !284
  store i32 %inc26, i32* %len25, align 4, !dbg !284
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then22
  br label %if.end43, !dbg !285

if.else27:                                        ; preds = %for.body14
  %base28 = getelementptr inbounds %struct.anon, %struct.anon* %cur, i32 0, i32 0, !dbg !286
  %15 = load i32, i32* %base28, align 4, !dbg !286
  %cmp29 = icmp ne i32 %15, -1, !dbg !289
  br i1 %cmp29, label %if.then31, label %if.end42, !dbg !290

if.then31:                                        ; preds = %if.else27
  %base32 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 0, !dbg !291
  %16 = load i32, i32* %base32, align 4, !dbg !291
  %cmp33 = icmp eq i32 %16, -1, !dbg !294
  br i1 %cmp33, label %if.then39, label %lor.lhs.false, !dbg !295

lor.lhs.false:                                    ; preds = %if.then31
  %len35 = getelementptr inbounds %struct.anon, %struct.anon* %cur, i32 0, i32 1, !dbg !296
  %17 = load i32, i32* %len35, align 4, !dbg !296
  %len36 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 1, !dbg !298
  %18 = load i32, i32* %len36, align 4, !dbg !298
  %cmp37 = icmp sgt i32 %17, %18, !dbg !299
  br i1 %cmp37, label %if.then39, label %if.end40, !dbg !300

if.then39:                                        ; preds = %lor.lhs.false, %if.then31
  %19 = bitcast %struct.anon* %best to i8*, !dbg !301
  %20 = bitcast %struct.anon* %cur to i8*, !dbg !301
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %19, i8* %20, i64 8, i32 4, i1 false), !dbg !301
  br label %if.end40, !dbg !302

if.end40:                                         ; preds = %if.then39, %lor.lhs.false
  %base41 = getelementptr inbounds %struct.anon, %struct.anon* %cur, i32 0, i32 0, !dbg !303
  store i32 -1, i32* %base41, align 4, !dbg !304
  br label %if.end42, !dbg !305

if.end42:                                         ; preds = %if.end40, %if.else27
  br label %if.end43

if.end43:                                         ; preds = %if.end42, %if.end
  br label %for.inc44, !dbg !306

for.inc44:                                        ; preds = %if.end43
  %21 = load i32, i32* %i, align 4, !dbg !307
  %inc45 = add nsw i32 %21, 1, !dbg !307
  store i32 %inc45, i32* %i, align 4, !dbg !307
  br label %for.cond11, !dbg !309

for.end46:                                        ; preds = %for.cond11
  %base47 = getelementptr inbounds %struct.anon, %struct.anon* %cur, i32 0, i32 0, !dbg !310
  %22 = load i32, i32* %base47, align 4, !dbg !310
  %cmp48 = icmp ne i32 %22, -1, !dbg !312
  br i1 %cmp48, label %if.then50, label %if.end61, !dbg !313

if.then50:                                        ; preds = %for.end46
  %base51 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 0, !dbg !314
  %23 = load i32, i32* %base51, align 4, !dbg !314
  %cmp52 = icmp eq i32 %23, -1, !dbg !317
  br i1 %cmp52, label %if.then59, label %lor.lhs.false54, !dbg !318

lor.lhs.false54:                                  ; preds = %if.then50
  %len55 = getelementptr inbounds %struct.anon, %struct.anon* %cur, i32 0, i32 1, !dbg !319
  %24 = load i32, i32* %len55, align 4, !dbg !319
  %len56 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 1, !dbg !321
  %25 = load i32, i32* %len56, align 4, !dbg !321
  %cmp57 = icmp sgt i32 %24, %25, !dbg !322
  br i1 %cmp57, label %if.then59, label %if.end60, !dbg !323

if.then59:                                        ; preds = %lor.lhs.false54, %if.then50
  %26 = bitcast %struct.anon* %best to i8*, !dbg !324
  %27 = bitcast %struct.anon* %cur to i8*, !dbg !324
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %26, i8* %27, i64 8, i32 4, i1 false), !dbg !324
  br label %if.end60, !dbg !325

if.end60:                                         ; preds = %if.then59, %lor.lhs.false54
  br label %if.end61, !dbg !326

if.end61:                                         ; preds = %if.end60, %for.end46
  %base62 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 0, !dbg !327
  %28 = load i32, i32* %base62, align 4, !dbg !327
  %cmp63 = icmp ne i32 %28, -1, !dbg !329
  br i1 %cmp63, label %land.lhs.true, label %if.end70, !dbg !330

land.lhs.true:                                    ; preds = %if.end61
  %len65 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 1, !dbg !331
  %29 = load i32, i32* %len65, align 4, !dbg !331
  %cmp66 = icmp slt i32 %29, 2, !dbg !333
  br i1 %cmp66, label %if.then68, label %if.end70, !dbg !334

if.then68:                                        ; preds = %land.lhs.true
  %base69 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 0, !dbg !335
  store i32 -1, i32* %base69, align 4, !dbg !336
  br label %if.end70, !dbg !337

if.end70:                                         ; preds = %if.then68, %land.lhs.true, %if.end61
  %arraydecay71 = getelementptr inbounds [46 x i8], [46 x i8]* %tmp, i32 0, i32 0, !dbg !338
  store i8* %arraydecay71, i8** %tp, align 8, !dbg !339
  store i32 0, i32* %i, align 4, !dbg !340
  br label %for.cond72, !dbg !342

for.cond72:                                       ; preds = %for.inc139, %if.end70
  %30 = load i32, i32* %i, align 4, !dbg !343
  %cmp73 = icmp slt i32 %30, 8, !dbg !346
  br i1 %cmp73, label %for.body75, label %for.end141, !dbg !347

for.body75:                                       ; preds = %for.cond72
  %base76 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 0, !dbg !348
  %31 = load i32, i32* %base76, align 4, !dbg !348
  %cmp77 = icmp ne i32 %31, -1, !dbg !351
  br i1 %cmp77, label %land.lhs.true79, label %if.end94, !dbg !352

land.lhs.true79:                                  ; preds = %for.body75
  %32 = load i32, i32* %i, align 4, !dbg !353
  %base80 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 0, !dbg !355
  %33 = load i32, i32* %base80, align 4, !dbg !355
  %cmp81 = icmp sge i32 %32, %33, !dbg !356
  br i1 %cmp81, label %land.lhs.true83, label %if.end94, !dbg !357

land.lhs.true83:                                  ; preds = %land.lhs.true79
  %34 = load i32, i32* %i, align 4, !dbg !358
  %base84 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 0, !dbg !359
  %35 = load i32, i32* %base84, align 4, !dbg !359
  %len85 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 1, !dbg !360
  %36 = load i32, i32* %len85, align 4, !dbg !360
  %add = add nsw i32 %35, %36, !dbg !361
  %cmp86 = icmp slt i32 %34, %add, !dbg !362
  br i1 %cmp86, label %if.then88, label %if.end94, !dbg !363

if.then88:                                        ; preds = %land.lhs.true83
  %37 = load i32, i32* %i, align 4, !dbg !365
  %base89 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 0, !dbg !368
  %38 = load i32, i32* %base89, align 4, !dbg !368
  %cmp90 = icmp eq i32 %37, %38, !dbg !369
  br i1 %cmp90, label %if.then92, label %if.end93, !dbg !370

if.then92:                                        ; preds = %if.then88
  %39 = load i8*, i8** %tp, align 8, !dbg !371
  %incdec.ptr = getelementptr inbounds i8, i8* %39, i32 1, !dbg !371
  store i8* %incdec.ptr, i8** %tp, align 8, !dbg !371
  store i8 58, i8* %39, align 1, !dbg !372
  br label %if.end93, !dbg !373

if.end93:                                         ; preds = %if.then92, %if.then88
  br label %for.inc139, !dbg !374

if.end94:                                         ; preds = %land.lhs.true83, %land.lhs.true79, %for.body75
  %40 = load i32, i32* %i, align 4, !dbg !375
  %cmp95 = icmp ne i32 %40, 0, !dbg !377
  br i1 %cmp95, label %if.then97, label %if.end99, !dbg !378

if.then97:                                        ; preds = %if.end94
  %41 = load i8*, i8** %tp, align 8, !dbg !379
  %incdec.ptr98 = getelementptr inbounds i8, i8* %41, i32 1, !dbg !379
  store i8* %incdec.ptr98, i8** %tp, align 8, !dbg !379
  store i8 58, i8* %41, align 1, !dbg !380
  br label %if.end99, !dbg !381

if.end99:                                         ; preds = %if.then97, %if.end94
  %42 = load i32, i32* %i, align 4, !dbg !382
  %cmp100 = icmp eq i32 %42, 6, !dbg !384
  br i1 %cmp100, label %land.lhs.true102, label %if.end134, !dbg !385

land.lhs.true102:                                 ; preds = %if.end99
  %base103 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 0, !dbg !386
  %43 = load i32, i32* %base103, align 4, !dbg !386
  %cmp104 = icmp eq i32 %43, 0, !dbg !388
  br i1 %cmp104, label %land.lhs.true106, label %if.end134, !dbg !389

land.lhs.true106:                                 ; preds = %land.lhs.true102
  %len107 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 1, !dbg !390
  %44 = load i32, i32* %len107, align 4, !dbg !390
  %cmp108 = icmp eq i32 %44, 6, !dbg !392
  br i1 %cmp108, label %if.then126, label %lor.lhs.false110, !dbg !393

lor.lhs.false110:                                 ; preds = %land.lhs.true106
  %len111 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 1, !dbg !394
  %45 = load i32, i32* %len111, align 4, !dbg !394
  %cmp112 = icmp eq i32 %45, 7, !dbg !395
  br i1 %cmp112, label %land.lhs.true114, label %lor.lhs.false118, !dbg !396

land.lhs.true114:                                 ; preds = %lor.lhs.false110
  %arrayidx115 = getelementptr inbounds [8 x i32], [8 x i32]* %words, i64 0, i64 7, !dbg !397
  %46 = load i32, i32* %arrayidx115, align 4, !dbg !397
  %cmp116 = icmp ne i32 %46, 1, !dbg !398
  br i1 %cmp116, label %if.then126, label %lor.lhs.false118, !dbg !399

lor.lhs.false118:                                 ; preds = %land.lhs.true114, %lor.lhs.false110
  %len119 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 1, !dbg !400
  %47 = load i32, i32* %len119, align 4, !dbg !400
  %cmp120 = icmp eq i32 %47, 5, !dbg !401
  br i1 %cmp120, label %land.lhs.true122, label %if.end134, !dbg !402

land.lhs.true122:                                 ; preds = %lor.lhs.false118
  %arrayidx123 = getelementptr inbounds [8 x i32], [8 x i32]* %words, i64 0, i64 5, !dbg !403
  %48 = load i32, i32* %arrayidx123, align 4, !dbg !403
  %cmp124 = icmp eq i32 %48, 65535, !dbg !404
  br i1 %cmp124, label %if.then126, label %if.end134, !dbg !405

if.then126:                                       ; preds = %land.lhs.true122, %land.lhs.true114, %land.lhs.true106
  call void @llvm.dbg.declare(metadata i32* %err, metadata !407, metadata !133), !dbg !409
  %49 = load i8*, i8** %src.addr, align 8, !dbg !410
  %add.ptr = getelementptr inbounds i8, i8* %49, i64 12, !dbg !411
  %50 = load i8*, i8** %tp, align 8, !dbg !412
  %51 = load i8*, i8** %tp, align 8, !dbg !413
  %arraydecay128 = getelementptr inbounds [46 x i8], [46 x i8]* %tmp, i32 0, i32 0, !dbg !414
  %sub.ptr.lhs.cast = ptrtoint i8* %51 to i64, !dbg !415
  %sub.ptr.rhs.cast = ptrtoint i8* %arraydecay128 to i64, !dbg !415
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !415
  %sub129 = sub i64 46, %sub.ptr.sub, !dbg !416
  %call = call i32 @inet_ntop4(i8* %add.ptr, i8* %50, i64 %sub129), !dbg !417
  store i32 %call, i32* %err, align 4, !dbg !409
  %52 = load i32, i32* %err, align 4, !dbg !418
  %tobool = icmp ne i32 %52, 0, !dbg !418
  br i1 %tobool, label %if.then130, label %if.end131, !dbg !420

if.then130:                                       ; preds = %if.then126
  %53 = load i32, i32* %err, align 4, !dbg !421
  store i32 %53, i32* %retval, align 4, !dbg !422
  br label %return, !dbg !422

if.end131:                                        ; preds = %if.then126
  %54 = load i8*, i8** %tp, align 8, !dbg !423
  %call132 = call i64 @strlen(i8* %54) #6, !dbg !424
  %55 = load i8*, i8** %tp, align 8, !dbg !425
  %add.ptr133 = getelementptr inbounds i8, i8* %55, i64 %call132, !dbg !425
  store i8* %add.ptr133, i8** %tp, align 8, !dbg !425
  br label %for.end141, !dbg !426

if.end134:                                        ; preds = %land.lhs.true122, %lor.lhs.false118, %land.lhs.true102, %if.end99
  %56 = load i8*, i8** %tp, align 8, !dbg !427
  %57 = load i32, i32* %i, align 4, !dbg !428
  %idxprom135 = sext i32 %57 to i64, !dbg !429
  %arrayidx136 = getelementptr inbounds [8 x i32], [8 x i32]* %words, i64 0, i64 %idxprom135, !dbg !429
  %58 = load i32, i32* %arrayidx136, align 4, !dbg !429
  %call137 = call i32 (i8*, i8*, ...) @sprintf(i8* %56, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i32 0, i32 0), i32 %58) #5, !dbg !430
  %59 = load i8*, i8** %tp, align 8, !dbg !431
  %idx.ext = sext i32 %call137 to i64, !dbg !431
  %add.ptr138 = getelementptr inbounds i8, i8* %59, i64 %idx.ext, !dbg !431
  store i8* %add.ptr138, i8** %tp, align 8, !dbg !431
  br label %for.inc139, !dbg !432

for.inc139:                                       ; preds = %if.end134, %if.end93
  %60 = load i32, i32* %i, align 4, !dbg !433
  %inc140 = add nsw i32 %60, 1, !dbg !433
  store i32 %inc140, i32* %i, align 4, !dbg !433
  br label %for.cond72, !dbg !435

for.end141:                                       ; preds = %if.end131, %for.cond72
  %base142 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 0, !dbg !436
  %61 = load i32, i32* %base142, align 4, !dbg !436
  %cmp143 = icmp ne i32 %61, -1, !dbg !438
  br i1 %cmp143, label %land.lhs.true145, label %if.end154, !dbg !439

land.lhs.true145:                                 ; preds = %for.end141
  %base146 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 0, !dbg !440
  %62 = load i32, i32* %base146, align 4, !dbg !440
  %len147 = getelementptr inbounds %struct.anon, %struct.anon* %best, i32 0, i32 1, !dbg !442
  %63 = load i32, i32* %len147, align 4, !dbg !442
  %add148 = add nsw i32 %62, %63, !dbg !443
  %conv149 = sext i32 %add148 to i64, !dbg !444
  %cmp150 = icmp eq i64 %conv149, 8, !dbg !445
  br i1 %cmp150, label %if.then152, label %if.end154, !dbg !446

if.then152:                                       ; preds = %land.lhs.true145
  %64 = load i8*, i8** %tp, align 8, !dbg !447
  %incdec.ptr153 = getelementptr inbounds i8, i8* %64, i32 1, !dbg !447
  store i8* %incdec.ptr153, i8** %tp, align 8, !dbg !447
  store i8 58, i8* %64, align 1, !dbg !448
  br label %if.end154, !dbg !449

if.end154:                                        ; preds = %if.then152, %land.lhs.true145, %for.end141
  %65 = load i8*, i8** %tp, align 8, !dbg !450
  %incdec.ptr155 = getelementptr inbounds i8, i8* %65, i32 1, !dbg !450
  store i8* %incdec.ptr155, i8** %tp, align 8, !dbg !450
  store i8 0, i8* %65, align 1, !dbg !451
  %66 = load i8*, i8** %tp, align 8, !dbg !452
  %arraydecay156 = getelementptr inbounds [46 x i8], [46 x i8]* %tmp, i32 0, i32 0, !dbg !454
  %sub.ptr.lhs.cast157 = ptrtoint i8* %66 to i64, !dbg !455
  %sub.ptr.rhs.cast158 = ptrtoint i8* %arraydecay156 to i64, !dbg !455
  %sub.ptr.sub159 = sub i64 %sub.ptr.lhs.cast157, %sub.ptr.rhs.cast158, !dbg !455
  %67 = load i64, i64* %size.addr, align 8, !dbg !456
  %cmp160 = icmp ugt i64 %sub.ptr.sub159, %67, !dbg !457
  br i1 %cmp160, label %if.then162, label %if.end163, !dbg !458

if.then162:                                       ; preds = %if.end154
  store i32 -28, i32* %retval, align 4, !dbg !459
  br label %return, !dbg !459

if.end163:                                        ; preds = %if.end154
  %68 = load i8*, i8** %dst.addr, align 8, !dbg !461
  %arraydecay164 = getelementptr inbounds [46 x i8], [46 x i8]* %tmp, i32 0, i32 0, !dbg !462
  %call165 = call i8* @strcpy(i8* %68, i8* %arraydecay164) #5, !dbg !463
  store i32 0, i32* %retval, align 4, !dbg !464
  br label %return, !dbg !464

return:                                           ; preds = %if.end163, %if.then162, %if.then130
  %69 = load i32, i32* %retval, align 4, !dbg !465
  ret i32 %69, !dbg !465
}

; Function Attrs: nounwind uwtable
define i32 @uv_inet_pton(i32 %af, i8* %src, i8* %dst) #0 !dbg !99 {
entry:
  %retval = alloca i32, align 4
  %af.addr = alloca i32, align 4
  %src.addr = alloca i8*, align 8
  %dst.addr = alloca i8*, align 8
  %len = alloca i32, align 4
  %tmp = alloca [46 x i8], align 16
  %s = alloca i8*, align 8
  %p = alloca i8*, align 8
  store i32 %af, i32* %af.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %af.addr, metadata !466, metadata !133), !dbg !467
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !468, metadata !133), !dbg !469
  store i8* %dst, i8** %dst.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dst.addr, metadata !470, metadata !133), !dbg !471
  %0 = load i8*, i8** %src.addr, align 8, !dbg !472
  %cmp = icmp eq i8* %0, null, !dbg !474
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !475

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %dst.addr, align 8, !dbg !476
  %cmp1 = icmp eq i8* %1, null, !dbg !478
  br i1 %cmp1, label %if.then, label %if.end, !dbg !479

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !480
  br label %return, !dbg !480

if.end:                                           ; preds = %lor.lhs.false
  %2 = load i32, i32* %af.addr, align 4, !dbg !481
  switch i32 %2, label %sw.default [
    i32 2, label %sw.bb
    i32 10, label %sw.bb2
  ], !dbg !482

sw.bb:                                            ; preds = %if.end
  %3 = load i8*, i8** %src.addr, align 8, !dbg !483
  %4 = load i8*, i8** %dst.addr, align 8, !dbg !485
  %call = call i32 @inet_pton4(i8* %3, i8* %4), !dbg !486
  store i32 %call, i32* %retval, align 4, !dbg !487
  br label %return, !dbg !487

sw.bb2:                                           ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %len, metadata !488, metadata !133), !dbg !490
  call void @llvm.dbg.declare(metadata [46 x i8]* %tmp, metadata !491, metadata !133), !dbg !492
  call void @llvm.dbg.declare(metadata i8** %s, metadata !493, metadata !133), !dbg !494
  call void @llvm.dbg.declare(metadata i8** %p, metadata !495, metadata !133), !dbg !496
  %5 = load i8*, i8** %src.addr, align 8, !dbg !497
  store i8* %5, i8** %s, align 8, !dbg !498
  %6 = load i8*, i8** %src.addr, align 8, !dbg !499
  %call5 = call i8* @strchr(i8* %6, i32 37) #6, !dbg !500
  store i8* %call5, i8** %p, align 8, !dbg !501
  %7 = load i8*, i8** %p, align 8, !dbg !502
  %cmp6 = icmp ne i8* %7, null, !dbg !504
  br i1 %cmp6, label %if.then7, label %if.end13, !dbg !505

if.then7:                                         ; preds = %sw.bb2
  %arraydecay = getelementptr inbounds [46 x i8], [46 x i8]* %tmp, i32 0, i32 0, !dbg !506
  store i8* %arraydecay, i8** %s, align 8, !dbg !508
  %8 = load i8*, i8** %p, align 8, !dbg !509
  %9 = load i8*, i8** %src.addr, align 8, !dbg !510
  %sub.ptr.lhs.cast = ptrtoint i8* %8 to i64, !dbg !511
  %sub.ptr.rhs.cast = ptrtoint i8* %9 to i64, !dbg !511
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !511
  %conv = trunc i64 %sub.ptr.sub to i32, !dbg !509
  store i32 %conv, i32* %len, align 4, !dbg !512
  %10 = load i32, i32* %len, align 4, !dbg !513
  %cmp8 = icmp sgt i32 %10, 45, !dbg !515
  br i1 %cmp8, label %if.then10, label %if.end11, !dbg !516

if.then10:                                        ; preds = %if.then7
  store i32 -22, i32* %retval, align 4, !dbg !517
  br label %return, !dbg !517

if.end11:                                         ; preds = %if.then7
  %11 = load i8*, i8** %s, align 8, !dbg !518
  %12 = load i8*, i8** %src.addr, align 8, !dbg !519
  %13 = load i32, i32* %len, align 4, !dbg !520
  %conv12 = sext i32 %13 to i64, !dbg !520
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %11, i8* %12, i64 %conv12, i32 1, i1 false), !dbg !521
  %14 = load i32, i32* %len, align 4, !dbg !522
  %idxprom = sext i32 %14 to i64, !dbg !523
  %15 = load i8*, i8** %s, align 8, !dbg !523
  %arrayidx = getelementptr inbounds i8, i8* %15, i64 %idxprom, !dbg !523
  store i8 0, i8* %arrayidx, align 1, !dbg !524
  br label %if.end13, !dbg !525

if.end13:                                         ; preds = %if.end11, %sw.bb2
  %16 = load i8*, i8** %s, align 8, !dbg !526
  %17 = load i8*, i8** %dst.addr, align 8, !dbg !527
  %call14 = call i32 @inet_pton6(i8* %16, i8* %17), !dbg !528
  store i32 %call14, i32* %retval, align 4, !dbg !529
  br label %return, !dbg !529

sw.default:                                       ; preds = %if.end
  store i32 -97, i32* %retval, align 4, !dbg !530
  br label %return, !dbg !530

return:                                           ; preds = %sw.default, %if.end13, %if.then10, %sw.bb, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !531
  ret i32 %18, !dbg !531
}

; Function Attrs: nounwind uwtable
define internal i32 @inet_pton4(i8* %src, i8* %dst) #0 !dbg !110 {
entry:
  %retval = alloca i32, align 4
  %src.addr = alloca i8*, align 8
  %dst.addr = alloca i8*, align 8
  %saw_digit = alloca i32, align 4
  %octets = alloca i32, align 4
  %ch = alloca i32, align 4
  %tmp = alloca [4 x i8], align 1
  %tp = alloca i8*, align 8
  %pch = alloca i8*, align 8
  %nw = alloca i32, align 4
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !532, metadata !133), !dbg !533
  store i8* %dst, i8** %dst.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dst.addr, metadata !534, metadata !133), !dbg !535
  call void @llvm.dbg.declare(metadata i32* %saw_digit, metadata !536, metadata !133), !dbg !537
  call void @llvm.dbg.declare(metadata i32* %octets, metadata !538, metadata !133), !dbg !539
  call void @llvm.dbg.declare(metadata i32* %ch, metadata !540, metadata !133), !dbg !541
  call void @llvm.dbg.declare(metadata [4 x i8]* %tmp, metadata !542, metadata !133), !dbg !546
  call void @llvm.dbg.declare(metadata i8** %tp, metadata !547, metadata !133), !dbg !548
  store i32 0, i32* %saw_digit, align 4, !dbg !549
  store i32 0, i32* %octets, align 4, !dbg !550
  %arraydecay = getelementptr inbounds [4 x i8], [4 x i8]* %tmp, i32 0, i32 0, !dbg !551
  store i8* %arraydecay, i8** %tp, align 8, !dbg !552
  store i8 0, i8* %arraydecay, align 1, !dbg !553
  br label %while.cond, !dbg !554

while.cond:                                       ; preds = %if.end38, %entry
  %0 = load i8*, i8** %src.addr, align 8, !dbg !555
  %incdec.ptr = getelementptr inbounds i8, i8* %0, i32 1, !dbg !555
  store i8* %incdec.ptr, i8** %src.addr, align 8, !dbg !555
  %1 = load i8, i8* %0, align 1, !dbg !557
  %conv = sext i8 %1 to i32, !dbg !557
  store i32 %conv, i32* %ch, align 4, !dbg !558
  %cmp = icmp ne i32 %conv, 0, !dbg !559
  br i1 %cmp, label %while.body, label %while.end, !dbg !560

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i8** %pch, metadata !561, metadata !133), !dbg !563
  %2 = load i32, i32* %ch, align 4, !dbg !564
  %call = call i8* @strchr(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @inet_pton4.digits, i32 0, i32 0), i32 %2) #6, !dbg !566
  store i8* %call, i8** %pch, align 8, !dbg !567
  %cmp4 = icmp ne i8* %call, null, !dbg !568
  br i1 %cmp4, label %if.then, label %if.else, !dbg !569

if.then:                                          ; preds = %while.body
  call void @llvm.dbg.declare(metadata i32* %nw, metadata !570, metadata !133), !dbg !572
  %3 = load i8*, i8** %tp, align 8, !dbg !573
  %4 = load i8, i8* %3, align 1, !dbg !574
  %conv7 = zext i8 %4 to i32, !dbg !574
  %mul = mul nsw i32 %conv7, 10, !dbg !575
  %conv8 = sext i32 %mul to i64, !dbg !574
  %5 = load i8*, i8** %pch, align 8, !dbg !576
  %sub.ptr.lhs.cast = ptrtoint i8* %5 to i64, !dbg !577
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, ptrtoint ([11 x i8]* @inet_pton4.digits to i64), !dbg !577
  %add = add nsw i64 %conv8, %sub.ptr.sub, !dbg !578
  %conv9 = trunc i64 %add to i32, !dbg !574
  store i32 %conv9, i32* %nw, align 4, !dbg !572
  %6 = load i32, i32* %saw_digit, align 4, !dbg !579
  %tobool = icmp ne i32 %6, 0, !dbg !579
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !581

land.lhs.true:                                    ; preds = %if.then
  %7 = load i8*, i8** %tp, align 8, !dbg !582
  %8 = load i8, i8* %7, align 1, !dbg !584
  %conv10 = zext i8 %8 to i32, !dbg !584
  %cmp11 = icmp eq i32 %conv10, 0, !dbg !585
  br i1 %cmp11, label %if.then13, label %if.end, !dbg !586

if.then13:                                        ; preds = %land.lhs.true
  store i32 -22, i32* %retval, align 4, !dbg !587
  br label %return, !dbg !587

if.end:                                           ; preds = %land.lhs.true, %if.then
  %9 = load i32, i32* %nw, align 4, !dbg !588
  %cmp14 = icmp ugt i32 %9, 255, !dbg !590
  br i1 %cmp14, label %if.then16, label %if.end17, !dbg !591

if.then16:                                        ; preds = %if.end
  store i32 -22, i32* %retval, align 4, !dbg !592
  br label %return, !dbg !592

if.end17:                                         ; preds = %if.end
  %10 = load i32, i32* %nw, align 4, !dbg !593
  %conv18 = trunc i32 %10 to i8, !dbg !593
  %11 = load i8*, i8** %tp, align 8, !dbg !594
  store i8 %conv18, i8* %11, align 1, !dbg !595
  %12 = load i32, i32* %saw_digit, align 4, !dbg !596
  %tobool19 = icmp ne i32 %12, 0, !dbg !596
  br i1 %tobool19, label %if.end25, label %if.then20, !dbg !598

if.then20:                                        ; preds = %if.end17
  %13 = load i32, i32* %octets, align 4, !dbg !599
  %inc = add nsw i32 %13, 1, !dbg !599
  store i32 %inc, i32* %octets, align 4, !dbg !599
  %cmp21 = icmp sgt i32 %inc, 4, !dbg !602
  br i1 %cmp21, label %if.then23, label %if.end24, !dbg !603

if.then23:                                        ; preds = %if.then20
  store i32 -22, i32* %retval, align 4, !dbg !604
  br label %return, !dbg !604

if.end24:                                         ; preds = %if.then20
  store i32 1, i32* %saw_digit, align 4, !dbg !605
  br label %if.end25, !dbg !606

if.end25:                                         ; preds = %if.end24, %if.end17
  br label %if.end38, !dbg !607

if.else:                                          ; preds = %while.body
  %14 = load i32, i32* %ch, align 4, !dbg !608
  %cmp26 = icmp eq i32 %14, 46, !dbg !611
  br i1 %cmp26, label %land.lhs.true28, label %if.else36, !dbg !612

land.lhs.true28:                                  ; preds = %if.else
  %15 = load i32, i32* %saw_digit, align 4, !dbg !613
  %tobool29 = icmp ne i32 %15, 0, !dbg !613
  br i1 %tobool29, label %if.then30, label %if.else36, !dbg !615

if.then30:                                        ; preds = %land.lhs.true28
  %16 = load i32, i32* %octets, align 4, !dbg !616
  %cmp31 = icmp eq i32 %16, 4, !dbg !619
  br i1 %cmp31, label %if.then33, label %if.end34, !dbg !620

if.then33:                                        ; preds = %if.then30
  store i32 -22, i32* %retval, align 4, !dbg !621
  br label %return, !dbg !621

if.end34:                                         ; preds = %if.then30
  %17 = load i8*, i8** %tp, align 8, !dbg !622
  %incdec.ptr35 = getelementptr inbounds i8, i8* %17, i32 1, !dbg !622
  store i8* %incdec.ptr35, i8** %tp, align 8, !dbg !622
  store i8 0, i8* %incdec.ptr35, align 1, !dbg !623
  store i32 0, i32* %saw_digit, align 4, !dbg !624
  br label %if.end37, !dbg !625

if.else36:                                        ; preds = %land.lhs.true28, %if.else
  store i32 -22, i32* %retval, align 4, !dbg !626
  br label %return, !dbg !626

if.end37:                                         ; preds = %if.end34
  br label %if.end38

if.end38:                                         ; preds = %if.end37, %if.end25
  br label %while.cond, !dbg !627

while.end:                                        ; preds = %while.cond
  %18 = load i32, i32* %octets, align 4, !dbg !629
  %cmp39 = icmp slt i32 %18, 4, !dbg !631
  br i1 %cmp39, label %if.then41, label %if.end42, !dbg !632

if.then41:                                        ; preds = %while.end
  store i32 -22, i32* %retval, align 4, !dbg !633
  br label %return, !dbg !633

if.end42:                                         ; preds = %while.end
  %19 = load i8*, i8** %dst.addr, align 8, !dbg !634
  %arraydecay43 = getelementptr inbounds [4 x i8], [4 x i8]* %tmp, i32 0, i32 0, !dbg !635
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %19, i8* %arraydecay43, i64 4, i32 1, i1 false), !dbg !635
  store i32 0, i32* %retval, align 4, !dbg !636
  br label %return, !dbg !636

return:                                           ; preds = %if.end42, %if.then41, %if.else36, %if.then33, %if.then23, %if.then16, %if.then13
  %20 = load i32, i32* %retval, align 4, !dbg !637
  ret i32 %20, !dbg !637
}

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

; Function Attrs: nounwind uwtable
define internal i32 @inet_pton6(i8* %src, i8* %dst) #0 !dbg !114 {
entry:
  %retval = alloca i32, align 4
  %src.addr = alloca i8*, align 8
  %dst.addr = alloca i8*, align 8
  %tmp = alloca [16 x i8], align 16
  %tp = alloca i8*, align 8
  %endp = alloca i8*, align 8
  %colonp = alloca i8*, align 8
  %xdigits = alloca i8*, align 8
  %curtok = alloca i8*, align 8
  %ch = alloca i32, align 4
  %seen_xdigits = alloca i32, align 4
  %val = alloca i32, align 4
  %pch = alloca i8*, align 8
  %err = alloca i32, align 4
  %n = alloca i32, align 4
  %i = alloca i32, align 4
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !638, metadata !133), !dbg !639
  store i8* %dst, i8** %dst.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dst.addr, metadata !640, metadata !133), !dbg !641
  call void @llvm.dbg.declare(metadata [16 x i8]* %tmp, metadata !642, metadata !133), !dbg !644
  call void @llvm.dbg.declare(metadata i8** %tp, metadata !645, metadata !133), !dbg !646
  call void @llvm.dbg.declare(metadata i8** %endp, metadata !647, metadata !133), !dbg !648
  call void @llvm.dbg.declare(metadata i8** %colonp, metadata !649, metadata !133), !dbg !650
  call void @llvm.dbg.declare(metadata i8** %xdigits, metadata !651, metadata !133), !dbg !652
  call void @llvm.dbg.declare(metadata i8** %curtok, metadata !653, metadata !133), !dbg !654
  call void @llvm.dbg.declare(metadata i32* %ch, metadata !655, metadata !133), !dbg !656
  call void @llvm.dbg.declare(metadata i32* %seen_xdigits, metadata !657, metadata !133), !dbg !658
  call void @llvm.dbg.declare(metadata i32* %val, metadata !659, metadata !133), !dbg !660
  %arraydecay = getelementptr inbounds [16 x i8], [16 x i8]* %tmp, i32 0, i32 0, !dbg !661
  store i8* %arraydecay, i8** %tp, align 8, !dbg !662
  call void @llvm.memset.p0i8.i64(i8* %arraydecay, i8 0, i64 16, i32 1, i1 false), !dbg !663
  %0 = load i8*, i8** %tp, align 8, !dbg !664
  %add.ptr = getelementptr inbounds i8, i8* %0, i64 16, !dbg !665
  store i8* %add.ptr, i8** %endp, align 8, !dbg !666
  store i8* null, i8** %colonp, align 8, !dbg !667
  %1 = load i8*, i8** %src.addr, align 8, !dbg !668
  %2 = load i8, i8* %1, align 1, !dbg !670
  %conv = sext i8 %2 to i32, !dbg !670
  %cmp = icmp eq i32 %conv, 58, !dbg !671
  br i1 %cmp, label %if.then, label %if.end14, !dbg !672

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %src.addr, align 8, !dbg !673
  %incdec.ptr = getelementptr inbounds i8, i8* %3, i32 1, !dbg !673
  store i8* %incdec.ptr, i8** %src.addr, align 8, !dbg !673
  %4 = load i8, i8* %incdec.ptr, align 1, !dbg !675
  %conv10 = sext i8 %4 to i32, !dbg !675
  %cmp11 = icmp ne i32 %conv10, 58, !dbg !676
  br i1 %cmp11, label %if.then13, label %if.end, !dbg !677

if.then13:                                        ; preds = %if.then
  store i32 -22, i32* %retval, align 4, !dbg !678
  br label %return, !dbg !678

if.end:                                           ; preds = %if.then
  br label %if.end14, !dbg !679

if.end14:                                         ; preds = %if.end, %entry
  %5 = load i8*, i8** %src.addr, align 8, !dbg !681
  store i8* %5, i8** %curtok, align 8, !dbg !682
  store i32 0, i32* %seen_xdigits, align 4, !dbg !683
  store i32 0, i32* %val, align 4, !dbg !684
  br label %while.cond, !dbg !685

while.cond:                                       ; preds = %if.end52, %if.end41, %if.end33, %if.end14
  %6 = load i8*, i8** %src.addr, align 8, !dbg !686
  %incdec.ptr15 = getelementptr inbounds i8, i8* %6, i32 1, !dbg !686
  store i8* %incdec.ptr15, i8** %src.addr, align 8, !dbg !686
  %7 = load i8, i8* %6, align 1, !dbg !688
  %conv16 = sext i8 %7 to i32, !dbg !688
  store i32 %conv16, i32* %ch, align 4, !dbg !689
  %cmp17 = icmp ne i32 %conv16, 0, !dbg !690
  br i1 %cmp17, label %while.body, label %while.end, !dbg !691

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i8** %pch, metadata !692, metadata !133), !dbg !694
  store i8* getelementptr inbounds ([17 x i8], [17 x i8]* @inet_pton6.xdigits_l, i32 0, i32 0), i8** %xdigits, align 8, !dbg !695
  %8 = load i32, i32* %ch, align 4, !dbg !697
  %call = call i8* @strchr(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @inet_pton6.xdigits_l, i32 0, i32 0), i32 %8) #6, !dbg !698
  store i8* %call, i8** %pch, align 8, !dbg !699
  %cmp20 = icmp eq i8* %call, null, !dbg !700
  br i1 %cmp20, label %if.then22, label %if.end24, !dbg !701

if.then22:                                        ; preds = %while.body
  store i8* getelementptr inbounds ([17 x i8], [17 x i8]* @inet_pton6.xdigits_u, i32 0, i32 0), i8** %xdigits, align 8, !dbg !702
  %9 = load i32, i32* %ch, align 4, !dbg !703
  %call23 = call i8* @strchr(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @inet_pton6.xdigits_u, i32 0, i32 0), i32 %9) #6, !dbg !704
  store i8* %call23, i8** %pch, align 8, !dbg !705
  br label %if.end24, !dbg !706

if.end24:                                         ; preds = %if.then22, %while.body
  %10 = load i8*, i8** %pch, align 8, !dbg !707
  %cmp25 = icmp ne i8* %10, null, !dbg !709
  br i1 %cmp25, label %if.then27, label %if.end34, !dbg !710

if.then27:                                        ; preds = %if.end24
  %11 = load i32, i32* %val, align 4, !dbg !711
  %shl = shl i32 %11, 4, !dbg !711
  store i32 %shl, i32* %val, align 4, !dbg !711
  %12 = load i8*, i8** %pch, align 8, !dbg !713
  %13 = load i8*, i8** %xdigits, align 8, !dbg !714
  %sub.ptr.lhs.cast = ptrtoint i8* %12 to i64, !dbg !715
  %sub.ptr.rhs.cast = ptrtoint i8* %13 to i64, !dbg !715
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !715
  %14 = load i32, i32* %val, align 4, !dbg !716
  %conv28 = zext i32 %14 to i64, !dbg !716
  %or = or i64 %conv28, %sub.ptr.sub, !dbg !716
  %conv29 = trunc i64 %or to i32, !dbg !716
  store i32 %conv29, i32* %val, align 4, !dbg !716
  %15 = load i32, i32* %seen_xdigits, align 4, !dbg !717
  %inc = add nsw i32 %15, 1, !dbg !717
  store i32 %inc, i32* %seen_xdigits, align 4, !dbg !717
  %cmp30 = icmp sgt i32 %inc, 4, !dbg !719
  br i1 %cmp30, label %if.then32, label %if.end33, !dbg !720

if.then32:                                        ; preds = %if.then27
  store i32 -22, i32* %retval, align 4, !dbg !721
  br label %return, !dbg !721

if.end33:                                         ; preds = %if.then27
  br label %while.cond, !dbg !722

if.end34:                                         ; preds = %if.end24
  %16 = load i32, i32* %ch, align 4, !dbg !723
  %cmp35 = icmp eq i32 %16, 58, !dbg !725
  br i1 %cmp35, label %if.then37, label %if.end62, !dbg !726

if.then37:                                        ; preds = %if.end34
  %17 = load i8*, i8** %src.addr, align 8, !dbg !727
  store i8* %17, i8** %curtok, align 8, !dbg !729
  %18 = load i32, i32* %seen_xdigits, align 4, !dbg !730
  %tobool = icmp ne i32 %18, 0, !dbg !730
  br i1 %tobool, label %if.else, label %if.then38, !dbg !732

if.then38:                                        ; preds = %if.then37
  %19 = load i8*, i8** %colonp, align 8, !dbg !733
  %tobool39 = icmp ne i8* %19, null, !dbg !733
  br i1 %tobool39, label %if.then40, label %if.end41, !dbg !736

if.then40:                                        ; preds = %if.then38
  store i32 -22, i32* %retval, align 4, !dbg !737
  br label %return, !dbg !737

if.end41:                                         ; preds = %if.then38
  %20 = load i8*, i8** %tp, align 8, !dbg !738
  store i8* %20, i8** %colonp, align 8, !dbg !739
  br label %while.cond, !dbg !740

if.else:                                          ; preds = %if.then37
  %21 = load i8*, i8** %src.addr, align 8, !dbg !741
  %22 = load i8, i8* %21, align 1, !dbg !743
  %conv42 = sext i8 %22 to i32, !dbg !743
  %cmp43 = icmp eq i32 %conv42, 0, !dbg !744
  br i1 %cmp43, label %if.then45, label %if.end46, !dbg !745

if.then45:                                        ; preds = %if.else
  store i32 -22, i32* %retval, align 4, !dbg !746
  br label %return, !dbg !746

if.end46:                                         ; preds = %if.else
  br label %if.end47

if.end47:                                         ; preds = %if.end46
  %23 = load i8*, i8** %tp, align 8, !dbg !748
  %add.ptr48 = getelementptr inbounds i8, i8* %23, i64 2, !dbg !750
  %24 = load i8*, i8** %endp, align 8, !dbg !751
  %cmp49 = icmp ugt i8* %add.ptr48, %24, !dbg !752
  br i1 %cmp49, label %if.then51, label %if.end52, !dbg !753

if.then51:                                        ; preds = %if.end47
  store i32 -22, i32* %retval, align 4, !dbg !754
  br label %return, !dbg !754

if.end52:                                         ; preds = %if.end47
  %25 = load i32, i32* %val, align 4, !dbg !755
  %shr = lshr i32 %25, 8, !dbg !756
  %conv53 = trunc i32 %shr to i8, !dbg !757
  %conv54 = zext i8 %conv53 to i32, !dbg !757
  %and = and i32 %conv54, 255, !dbg !758
  %conv55 = trunc i32 %and to i8, !dbg !757
  %26 = load i8*, i8** %tp, align 8, !dbg !759
  %incdec.ptr56 = getelementptr inbounds i8, i8* %26, i32 1, !dbg !759
  store i8* %incdec.ptr56, i8** %tp, align 8, !dbg !759
  store i8 %conv55, i8* %26, align 1, !dbg !760
  %27 = load i32, i32* %val, align 4, !dbg !761
  %conv57 = trunc i32 %27 to i8, !dbg !762
  %conv58 = zext i8 %conv57 to i32, !dbg !762
  %and59 = and i32 %conv58, 255, !dbg !763
  %conv60 = trunc i32 %and59 to i8, !dbg !762
  %28 = load i8*, i8** %tp, align 8, !dbg !764
  %incdec.ptr61 = getelementptr inbounds i8, i8* %28, i32 1, !dbg !764
  store i8* %incdec.ptr61, i8** %tp, align 8, !dbg !764
  store i8 %conv60, i8* %28, align 1, !dbg !765
  store i32 0, i32* %seen_xdigits, align 4, !dbg !766
  store i32 0, i32* %val, align 4, !dbg !767
  br label %while.cond, !dbg !768

if.end62:                                         ; preds = %if.end34
  %29 = load i32, i32* %ch, align 4, !dbg !769
  %cmp63 = icmp eq i32 %29, 46, !dbg !771
  br i1 %cmp63, label %land.lhs.true, label %if.end76, !dbg !772

land.lhs.true:                                    ; preds = %if.end62
  %30 = load i8*, i8** %tp, align 8, !dbg !773
  %add.ptr65 = getelementptr inbounds i8, i8* %30, i64 4, !dbg !775
  %31 = load i8*, i8** %endp, align 8, !dbg !776
  %cmp66 = icmp ule i8* %add.ptr65, %31, !dbg !777
  br i1 %cmp66, label %if.then68, label %if.end76, !dbg !778

if.then68:                                        ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i32* %err, metadata !779, metadata !133), !dbg !781
  %32 = load i8*, i8** %curtok, align 8, !dbg !782
  %33 = load i8*, i8** %tp, align 8, !dbg !783
  %call70 = call i32 @inet_pton4(i8* %32, i8* %33), !dbg !784
  store i32 %call70, i32* %err, align 4, !dbg !781
  %34 = load i32, i32* %err, align 4, !dbg !785
  %cmp71 = icmp eq i32 %34, 0, !dbg !787
  br i1 %cmp71, label %if.then73, label %if.end75, !dbg !788

if.then73:                                        ; preds = %if.then68
  %35 = load i8*, i8** %tp, align 8, !dbg !789
  %add.ptr74 = getelementptr inbounds i8, i8* %35, i64 4, !dbg !789
  store i8* %add.ptr74, i8** %tp, align 8, !dbg !789
  store i32 0, i32* %seen_xdigits, align 4, !dbg !791
  br label %while.end, !dbg !792

if.end75:                                         ; preds = %if.then68
  br label %if.end76, !dbg !793

if.end76:                                         ; preds = %if.end75, %land.lhs.true, %if.end62
  store i32 -22, i32* %retval, align 4, !dbg !794
  br label %return, !dbg !794

while.end:                                        ; preds = %if.then73, %while.cond
  %36 = load i32, i32* %seen_xdigits, align 4, !dbg !795
  %tobool77 = icmp ne i32 %36, 0, !dbg !795
  br i1 %tobool77, label %if.then78, label %if.end95, !dbg !797

if.then78:                                        ; preds = %while.end
  %37 = load i8*, i8** %tp, align 8, !dbg !798
  %add.ptr79 = getelementptr inbounds i8, i8* %37, i64 2, !dbg !801
  %38 = load i8*, i8** %endp, align 8, !dbg !802
  %cmp80 = icmp ugt i8* %add.ptr79, %38, !dbg !803
  br i1 %cmp80, label %if.then82, label %if.end83, !dbg !804

if.then82:                                        ; preds = %if.then78
  store i32 -22, i32* %retval, align 4, !dbg !805
  br label %return, !dbg !805

if.end83:                                         ; preds = %if.then78
  %39 = load i32, i32* %val, align 4, !dbg !806
  %shr84 = lshr i32 %39, 8, !dbg !807
  %conv85 = trunc i32 %shr84 to i8, !dbg !808
  %conv86 = zext i8 %conv85 to i32, !dbg !808
  %and87 = and i32 %conv86, 255, !dbg !809
  %conv88 = trunc i32 %and87 to i8, !dbg !808
  %40 = load i8*, i8** %tp, align 8, !dbg !810
  %incdec.ptr89 = getelementptr inbounds i8, i8* %40, i32 1, !dbg !810
  store i8* %incdec.ptr89, i8** %tp, align 8, !dbg !810
  store i8 %conv88, i8* %40, align 1, !dbg !811
  %41 = load i32, i32* %val, align 4, !dbg !812
  %conv90 = trunc i32 %41 to i8, !dbg !813
  %conv91 = zext i8 %conv90 to i32, !dbg !813
  %and92 = and i32 %conv91, 255, !dbg !814
  %conv93 = trunc i32 %and92 to i8, !dbg !813
  %42 = load i8*, i8** %tp, align 8, !dbg !815
  %incdec.ptr94 = getelementptr inbounds i8, i8* %42, i32 1, !dbg !815
  store i8* %incdec.ptr94, i8** %tp, align 8, !dbg !815
  store i8 %conv93, i8* %42, align 1, !dbg !816
  br label %if.end95, !dbg !817

if.end95:                                         ; preds = %if.end83, %while.end
  %43 = load i8*, i8** %colonp, align 8, !dbg !818
  %cmp96 = icmp ne i8* %43, null, !dbg !820
  br i1 %cmp96, label %if.then98, label %if.end118, !dbg !821

if.then98:                                        ; preds = %if.end95
  call void @llvm.dbg.declare(metadata i32* %n, metadata !822, metadata !133), !dbg !825
  %44 = load i8*, i8** %tp, align 8, !dbg !826
  %45 = load i8*, i8** %colonp, align 8, !dbg !827
  %sub.ptr.lhs.cast100 = ptrtoint i8* %44 to i64, !dbg !828
  %sub.ptr.rhs.cast101 = ptrtoint i8* %45 to i64, !dbg !828
  %sub.ptr.sub102 = sub i64 %sub.ptr.lhs.cast100, %sub.ptr.rhs.cast101, !dbg !828
  %conv103 = trunc i64 %sub.ptr.sub102 to i32, !dbg !826
  store i32 %conv103, i32* %n, align 4, !dbg !825
  call void @llvm.dbg.declare(metadata i32* %i, metadata !829, metadata !133), !dbg !830
  %46 = load i8*, i8** %tp, align 8, !dbg !831
  %47 = load i8*, i8** %endp, align 8, !dbg !833
  %cmp105 = icmp eq i8* %46, %47, !dbg !834
  br i1 %cmp105, label %if.then107, label %if.end108, !dbg !835

if.then107:                                       ; preds = %if.then98
  store i32 -22, i32* %retval, align 4, !dbg !836
  br label %return, !dbg !836

if.end108:                                        ; preds = %if.then98
  store i32 1, i32* %i, align 4, !dbg !837
  br label %for.cond, !dbg !839

for.cond:                                         ; preds = %for.inc, %if.end108
  %48 = load i32, i32* %i, align 4, !dbg !840
  %49 = load i32, i32* %n, align 4, !dbg !843
  %cmp109 = icmp sle i32 %48, %49, !dbg !844
  br i1 %cmp109, label %for.body, label %for.end, !dbg !845

for.body:                                         ; preds = %for.cond
  %50 = load i32, i32* %n, align 4, !dbg !846
  %51 = load i32, i32* %i, align 4, !dbg !848
  %sub = sub nsw i32 %50, %51, !dbg !849
  %idxprom = sext i32 %sub to i64, !dbg !850
  %52 = load i8*, i8** %colonp, align 8, !dbg !850
  %arrayidx = getelementptr inbounds i8, i8* %52, i64 %idxprom, !dbg !850
  %53 = load i8, i8* %arrayidx, align 1, !dbg !850
  %54 = load i32, i32* %i, align 4, !dbg !851
  %sub111 = sub nsw i32 0, %54, !dbg !852
  %idxprom112 = sext i32 %sub111 to i64, !dbg !853
  %55 = load i8*, i8** %endp, align 8, !dbg !853
  %arrayidx113 = getelementptr inbounds i8, i8* %55, i64 %idxprom112, !dbg !853
  store i8 %53, i8* %arrayidx113, align 1, !dbg !854
  %56 = load i32, i32* %n, align 4, !dbg !855
  %57 = load i32, i32* %i, align 4, !dbg !856
  %sub114 = sub nsw i32 %56, %57, !dbg !857
  %idxprom115 = sext i32 %sub114 to i64, !dbg !858
  %58 = load i8*, i8** %colonp, align 8, !dbg !858
  %arrayidx116 = getelementptr inbounds i8, i8* %58, i64 %idxprom115, !dbg !858
  store i8 0, i8* %arrayidx116, align 1, !dbg !859
  br label %for.inc, !dbg !860

for.inc:                                          ; preds = %for.body
  %59 = load i32, i32* %i, align 4, !dbg !861
  %inc117 = add nsw i32 %59, 1, !dbg !861
  store i32 %inc117, i32* %i, align 4, !dbg !861
  br label %for.cond, !dbg !863

for.end:                                          ; preds = %for.cond
  %60 = load i8*, i8** %endp, align 8, !dbg !864
  store i8* %60, i8** %tp, align 8, !dbg !865
  br label %if.end118, !dbg !866

if.end118:                                        ; preds = %for.end, %if.end95
  %61 = load i8*, i8** %tp, align 8, !dbg !867
  %62 = load i8*, i8** %endp, align 8, !dbg !869
  %cmp119 = icmp ne i8* %61, %62, !dbg !870
  br i1 %cmp119, label %if.then121, label %if.end122, !dbg !871

if.then121:                                       ; preds = %if.end118
  store i32 -22, i32* %retval, align 4, !dbg !872
  br label %return, !dbg !872

if.end122:                                        ; preds = %if.end118
  %63 = load i8*, i8** %dst.addr, align 8, !dbg !873
  %arraydecay123 = getelementptr inbounds [16 x i8], [16 x i8]* %tmp, i32 0, i32 0, !dbg !874
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %63, i8* %arraydecay123, i64 16, i32 1, i1 false), !dbg !874
  store i32 0, i32* %retval, align 4, !dbg !875
  br label %return, !dbg !875

return:                                           ; preds = %if.end122, %if.then121, %if.then107, %if.then82, %if.end76, %if.then51, %if.then45, %if.then40, %if.then32, %if.then13
  %64 = load i32, i32* %retval, align 4, !dbg !876
  ret i32 %64, !dbg !876
}

; Function Attrs: nounwind
declare i32 @snprintf(i8*, i64, i8*, ...) #4

; Function Attrs: nounwind
declare i8* @strncpy(i8*, i8*, i64) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #3

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #2

; Function Attrs: nounwind
declare i32 @sprintf(i8*, i8*, ...) #4

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }
attributes #6 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!129, !130}
!llvm.ident = !{!131}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !83, subprograms: !92, globals: !115)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/inet.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 177, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82}
!6 = !DIEnumerator(name: "UV_E2BIG", value: -7)
!7 = !DIEnumerator(name: "UV_EACCES", value: -13)
!8 = !DIEnumerator(name: "UV_EADDRINUSE", value: -98)
!9 = !DIEnumerator(name: "UV_EADDRNOTAVAIL", value: -99)
!10 = !DIEnumerator(name: "UV_EAFNOSUPPORT", value: -97)
!11 = !DIEnumerator(name: "UV_EAGAIN", value: -11)
!12 = !DIEnumerator(name: "UV_EAI_ADDRFAMILY", value: -3000)
!13 = !DIEnumerator(name: "UV_EAI_AGAIN", value: -3001)
!14 = !DIEnumerator(name: "UV_EAI_BADFLAGS", value: -3002)
!15 = !DIEnumerator(name: "UV_EAI_BADHINTS", value: -3013)
!16 = !DIEnumerator(name: "UV_EAI_CANCELED", value: -3003)
!17 = !DIEnumerator(name: "UV_EAI_FAIL", value: -3004)
!18 = !DIEnumerator(name: "UV_EAI_FAMILY", value: -3005)
!19 = !DIEnumerator(name: "UV_EAI_MEMORY", value: -3006)
!20 = !DIEnumerator(name: "UV_EAI_NODATA", value: -3007)
!21 = !DIEnumerator(name: "UV_EAI_NONAME", value: -3008)
!22 = !DIEnumerator(name: "UV_EAI_OVERFLOW", value: -3009)
!23 = !DIEnumerator(name: "UV_EAI_PROTOCOL", value: -3014)
!24 = !DIEnumerator(name: "UV_EAI_SERVICE", value: -3010)
!25 = !DIEnumerator(name: "UV_EAI_SOCKTYPE", value: -3011)
!26 = !DIEnumerator(name: "UV_EALREADY", value: -114)
!27 = !DIEnumerator(name: "UV_EBADF", value: -9)
!28 = !DIEnumerator(name: "UV_EBUSY", value: -16)
!29 = !DIEnumerator(name: "UV_ECANCELED", value: -125)
!30 = !DIEnumerator(name: "UV_ECHARSET", value: -4080)
!31 = !DIEnumerator(name: "UV_ECONNABORTED", value: -103)
!32 = !DIEnumerator(name: "UV_ECONNREFUSED", value: -111)
!33 = !DIEnumerator(name: "UV_ECONNRESET", value: -104)
!34 = !DIEnumerator(name: "UV_EDESTADDRREQ", value: -89)
!35 = !DIEnumerator(name: "UV_EEXIST", value: -17)
!36 = !DIEnumerator(name: "UV_EFAULT", value: -14)
!37 = !DIEnumerator(name: "UV_EFBIG", value: -27)
!38 = !DIEnumerator(name: "UV_EHOSTUNREACH", value: -113)
!39 = !DIEnumerator(name: "UV_EINTR", value: -4)
!40 = !DIEnumerator(name: "UV_EINVAL", value: -22)
!41 = !DIEnumerator(name: "UV_EIO", value: -5)
!42 = !DIEnumerator(name: "UV_EISCONN", value: -106)
!43 = !DIEnumerator(name: "UV_EISDIR", value: -21)
!44 = !DIEnumerator(name: "UV_ELOOP", value: -40)
!45 = !DIEnumerator(name: "UV_EMFILE", value: -24)
!46 = !DIEnumerator(name: "UV_EMSGSIZE", value: -90)
!47 = !DIEnumerator(name: "UV_ENAMETOOLONG", value: -36)
!48 = !DIEnumerator(name: "UV_ENETDOWN", value: -100)
!49 = !DIEnumerator(name: "UV_ENETUNREACH", value: -101)
!50 = !DIEnumerator(name: "UV_ENFILE", value: -23)
!51 = !DIEnumerator(name: "UV_ENOBUFS", value: -105)
!52 = !DIEnumerator(name: "UV_ENODEV", value: -19)
!53 = !DIEnumerator(name: "UV_ENOENT", value: -2)
!54 = !DIEnumerator(name: "UV_ENOMEM", value: -12)
!55 = !DIEnumerator(name: "UV_ENONET", value: -64)
!56 = !DIEnumerator(name: "UV_ENOPROTOOPT", value: -92)
!57 = !DIEnumerator(name: "UV_ENOSPC", value: -28)
!58 = !DIEnumerator(name: "UV_ENOSYS", value: -38)
!59 = !DIEnumerator(name: "UV_ENOTCONN", value: -107)
!60 = !DIEnumerator(name: "UV_ENOTDIR", value: -20)
!61 = !DIEnumerator(name: "UV_ENOTEMPTY", value: -39)
!62 = !DIEnumerator(name: "UV_ENOTSOCK", value: -88)
!63 = !DIEnumerator(name: "UV_ENOTSUP", value: -95)
!64 = !DIEnumerator(name: "UV_EPERM", value: -1)
!65 = !DIEnumerator(name: "UV_EPIPE", value: -32)
!66 = !DIEnumerator(name: "UV_EPROTO", value: -71)
!67 = !DIEnumerator(name: "UV_EPROTONOSUPPORT", value: -93)
!68 = !DIEnumerator(name: "UV_EPROTOTYPE", value: -91)
!69 = !DIEnumerator(name: "UV_ERANGE", value: -34)
!70 = !DIEnumerator(name: "UV_EROFS", value: -30)
!71 = !DIEnumerator(name: "UV_ESHUTDOWN", value: -108)
!72 = !DIEnumerator(name: "UV_ESPIPE", value: -29)
!73 = !DIEnumerator(name: "UV_ESRCH", value: -3)
!74 = !DIEnumerator(name: "UV_ETIMEDOUT", value: -110)
!75 = !DIEnumerator(name: "UV_ETXTBSY", value: -26)
!76 = !DIEnumerator(name: "UV_EXDEV", value: -18)
!77 = !DIEnumerator(name: "UV_UNKNOWN", value: -4094)
!78 = !DIEnumerator(name: "UV_EOF", value: -4095)
!79 = !DIEnumerator(name: "UV_ENXIO", value: -6)
!80 = !DIEnumerator(name: "UV_EMLINK", value: -31)
!81 = !DIEnumerator(name: "UV_EHOSTDOWN", value: -112)
!82 = !DIEnumerator(name: "UV_ERRNO_MAX", value: -4096)
!83 = !{!84, !85, !87, !90, !91}
!84 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !86, size: 64, align: 64)
!86 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!87 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !88, line: 62, baseType: !89)
!88 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!89 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!90 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!91 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!92 = !{!93, !99, !104, !109, !110, !114}
!93 = distinct !DISubprogram(name: "uv_inet_ntop", scope: !1, file: !1, line: 40, type: !94, isLocal: false, isDefinition: true, scopeLine: 40, flags: DIFlagPrototyped, isOptimized: false, variables: !98)
!94 = !DISubroutineType(types: !95)
!95 = !{!90, !90, !96, !85, !87}
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !97, size: 64, align: 64)
!97 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!98 = !{}
!99 = distinct !DISubprogram(name: "uv_inet_pton", scope: !1, file: !1, line: 157, type: !100, isLocal: false, isDefinition: true, scopeLine: 157, flags: DIFlagPrototyped, isOptimized: false, variables: !98)
!100 = !DISubroutineType(types: !101)
!101 = !{!90, !90, !102, !84}
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !86)
!104 = distinct !DISubprogram(name: "inet_ntop4", scope: !1, file: !1, line: 53, type: !105, isLocal: true, isDefinition: true, scopeLine: 53, flags: DIFlagPrototyped, isOptimized: false, variables: !98)
!105 = !DISubroutineType(types: !106)
!106 = !{!90, !107, !85, !87}
!107 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !108, size: 64, align: 64)
!108 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !91)
!109 = distinct !DISubprogram(name: "inet_ntop6", scope: !1, file: !1, line: 68, type: !105, isLocal: true, isDefinition: true, scopeLine: 68, flags: DIFlagPrototyped, isOptimized: false, variables: !98)
!110 = distinct !DISubprogram(name: "inet_pton4", scope: !1, file: !1, line: 186, type: !111, isLocal: true, isDefinition: true, scopeLine: 186, flags: DIFlagPrototyped, isOptimized: false, variables: !98)
!111 = !DISubroutineType(types: !112)
!112 = !{!90, !102, !113}
!113 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !91, size: 64, align: 64)
!114 = distinct !DISubprogram(name: "inet_pton6", scope: !1, file: !1, line: 225, type: !111, isLocal: true, isDefinition: true, scopeLine: 225, flags: DIFlagPrototyped, isOptimized: false, variables: !98)
!115 = !{!116, !120, !124, !128}
!116 = !DIGlobalVariable(name: "fmt", scope: !104, file: !1, line: 54, type: !117, isLocal: true, isDefinition: true, variable: [12 x i8]* @inet_ntop4.fmt)
!117 = !DICompositeType(tag: DW_TAG_array_type, baseType: !103, size: 96, align: 8, elements: !118)
!118 = !{!119}
!119 = !DISubrange(count: 12)
!120 = !DIGlobalVariable(name: "digits", scope: !110, file: !1, line: 187, type: !121, isLocal: true, isDefinition: true, variable: [11 x i8]* @inet_pton4.digits)
!121 = !DICompositeType(tag: DW_TAG_array_type, baseType: !103, size: 88, align: 8, elements: !122)
!122 = !{!123}
!123 = !DISubrange(count: 11)
!124 = !DIGlobalVariable(name: "xdigits_l", scope: !114, file: !1, line: 226, type: !125, isLocal: true, isDefinition: true, variable: [17 x i8]* @inet_pton6.xdigits_l)
!125 = !DICompositeType(tag: DW_TAG_array_type, baseType: !103, size: 136, align: 8, elements: !126)
!126 = !{!127}
!127 = !DISubrange(count: 17)
!128 = !DIGlobalVariable(name: "xdigits_u", scope: !114, file: !1, line: 227, type: !125, isLocal: true, isDefinition: true, variable: [17 x i8]* @inet_pton6.xdigits_u)
!129 = !{i32 2, !"Dwarf Version", i32 4}
!130 = !{i32 2, !"Debug Info Version", i32 3}
!131 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!132 = !DILocalVariable(name: "af", arg: 1, scope: !93, file: !1, line: 40, type: !90)
!133 = !DIExpression()
!134 = !DILocation(line: 40, column: 22, scope: !93)
!135 = !DILocalVariable(name: "src", arg: 2, scope: !93, file: !1, line: 40, type: !96)
!136 = !DILocation(line: 40, column: 38, scope: !93)
!137 = !DILocalVariable(name: "dst", arg: 3, scope: !93, file: !1, line: 40, type: !85)
!138 = !DILocation(line: 40, column: 49, scope: !93)
!139 = !DILocalVariable(name: "size", arg: 4, scope: !93, file: !1, line: 40, type: !87)
!140 = !DILocation(line: 40, column: 61, scope: !93)
!141 = !DILocation(line: 41, column: 11, scope: !93)
!142 = !DILocation(line: 41, column: 3, scope: !93)
!143 = !DILocation(line: 43, column: 24, scope: !144)
!144 = distinct !DILexicalBlock(scope: !93, file: !1, line: 41, column: 15)
!145 = !DILocation(line: 43, column: 29, scope: !144)
!146 = !DILocation(line: 43, column: 34, scope: !144)
!147 = !DILocation(line: 43, column: 13, scope: !144)
!148 = !DILocation(line: 43, column: 5, scope: !144)
!149 = !DILocation(line: 45, column: 24, scope: !144)
!150 = !DILocation(line: 45, column: 29, scope: !144)
!151 = !DILocation(line: 45, column: 34, scope: !144)
!152 = !DILocation(line: 45, column: 13, scope: !144)
!153 = !DILocation(line: 45, column: 5, scope: !144)
!154 = !DILocation(line: 47, column: 5, scope: !144)
!155 = !DILocation(line: 50, column: 1, scope: !93)
!156 = !DILocalVariable(name: "src", arg: 1, scope: !104, file: !1, line: 53, type: !107)
!157 = !DILocation(line: 53, column: 44, scope: !104)
!158 = !DILocalVariable(name: "dst", arg: 2, scope: !104, file: !1, line: 53, type: !85)
!159 = !DILocation(line: 53, column: 55, scope: !104)
!160 = !DILocalVariable(name: "size", arg: 3, scope: !104, file: !1, line: 53, type: !87)
!161 = !DILocation(line: 53, column: 67, scope: !104)
!162 = !DILocalVariable(name: "tmp", scope: !104, file: !1, line: 55, type: !163)
!163 = !DICompositeType(tag: DW_TAG_array_type, baseType: !86, size: 128, align: 8, elements: !164)
!164 = !{!165}
!165 = !DISubrange(count: 16)
!166 = !DILocation(line: 55, column: 8, scope: !104)
!167 = !DILocalVariable(name: "l", scope: !104, file: !1, line: 56, type: !90)
!168 = !DILocation(line: 56, column: 7, scope: !104)
!169 = !DILocation(line: 58, column: 16, scope: !104)
!170 = !DILocation(line: 58, column: 39, scope: !104)
!171 = !DILocation(line: 58, column: 47, scope: !104)
!172 = !DILocation(line: 58, column: 55, scope: !104)
!173 = !DILocation(line: 58, column: 63, scope: !104)
!174 = !DILocation(line: 58, column: 7, scope: !104)
!175 = !DILocation(line: 58, column: 5, scope: !104)
!176 = !DILocation(line: 59, column: 7, scope: !177)
!177 = distinct !DILexicalBlock(scope: !104, file: !1, line: 59, column: 7)
!178 = !DILocation(line: 59, column: 9, scope: !177)
!179 = !DILocation(line: 59, column: 14, scope: !177)
!180 = !DILocation(line: 59, column: 26, scope: !181)
!181 = !DILexicalBlockFile(scope: !177, file: !1, discriminator: 1)
!182 = !DILocation(line: 59, column: 17, scope: !181)
!183 = !DILocation(line: 59, column: 31, scope: !181)
!184 = !DILocation(line: 59, column: 28, scope: !181)
!185 = !DILocation(line: 59, column: 7, scope: !181)
!186 = !DILocation(line: 60, column: 5, scope: !187)
!187 = distinct !DILexicalBlock(scope: !177, file: !1, line: 59, column: 37)
!188 = !DILocation(line: 62, column: 11, scope: !104)
!189 = !DILocation(line: 62, column: 16, scope: !104)
!190 = !DILocation(line: 62, column: 21, scope: !104)
!191 = !DILocation(line: 62, column: 3, scope: !104)
!192 = !DILocation(line: 63, column: 7, scope: !104)
!193 = !DILocation(line: 63, column: 12, scope: !104)
!194 = !DILocation(line: 63, column: 3, scope: !104)
!195 = !DILocation(line: 63, column: 17, scope: !104)
!196 = !DILocation(line: 64, column: 3, scope: !104)
!197 = !DILocation(line: 65, column: 1, scope: !104)
!198 = !DILocalVariable(name: "src", arg: 1, scope: !109, file: !1, line: 68, type: !107)
!199 = !DILocation(line: 68, column: 44, scope: !109)
!200 = !DILocalVariable(name: "dst", arg: 2, scope: !109, file: !1, line: 68, type: !85)
!201 = !DILocation(line: 68, column: 55, scope: !109)
!202 = !DILocalVariable(name: "size", arg: 3, scope: !109, file: !1, line: 68, type: !87)
!203 = !DILocation(line: 68, column: 67, scope: !109)
!204 = !DILocalVariable(name: "tmp", scope: !109, file: !1, line: 76, type: !205)
!205 = !DICompositeType(tag: DW_TAG_array_type, baseType: !86, size: 368, align: 8, elements: !206)
!206 = !{!207}
!207 = !DISubrange(count: 46)
!208 = !DILocation(line: 76, column: 8, scope: !109)
!209 = !DILocalVariable(name: "tp", scope: !109, file: !1, line: 76, type: !85)
!210 = !DILocation(line: 76, column: 36, scope: !109)
!211 = !DILocalVariable(name: "best", scope: !109, file: !1, line: 77, type: !212)
!212 = !DICompositeType(tag: DW_TAG_structure_type, scope: !109, file: !1, line: 77, size: 64, align: 32, elements: !213)
!213 = !{!214, !215}
!214 = !DIDerivedType(tag: DW_TAG_member, name: "base", scope: !212, file: !1, line: 77, baseType: !90, size: 32, align: 32)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !212, file: !1, line: 77, baseType: !90, size: 32, align: 32, offset: 32)
!216 = !DILocation(line: 77, column: 29, scope: !109)
!217 = !DILocalVariable(name: "cur", scope: !109, file: !1, line: 77, type: !212)
!218 = !DILocation(line: 77, column: 35, scope: !109)
!219 = !DILocalVariable(name: "words", scope: !109, file: !1, line: 78, type: !220)
!220 = !DICompositeType(tag: DW_TAG_array_type, baseType: !221, size: 256, align: 32, elements: !222)
!221 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!222 = !{!223}
!223 = !DISubrange(count: 8)
!224 = !DILocation(line: 78, column: 16, scope: !109)
!225 = !DILocalVariable(name: "i", scope: !109, file: !1, line: 79, type: !90)
!226 = !DILocation(line: 79, column: 7, scope: !109)
!227 = !DILocation(line: 86, column: 3, scope: !109)
!228 = !DILocation(line: 87, column: 10, scope: !229)
!229 = distinct !DILexicalBlock(scope: !109, file: !1, line: 87, column: 3)
!230 = !DILocation(line: 87, column: 8, scope: !229)
!231 = !DILocation(line: 87, column: 15, scope: !232)
!232 = !DILexicalBlockFile(scope: !233, file: !1, discriminator: 1)
!233 = distinct !DILexicalBlock(scope: !229, file: !1, line: 87, column: 3)
!234 = !DILocation(line: 87, column: 17, scope: !232)
!235 = !DILocation(line: 87, column: 3, scope: !232)
!236 = !DILocation(line: 88, column: 26, scope: !233)
!237 = !DILocation(line: 88, column: 22, scope: !233)
!238 = !DILocation(line: 88, column: 39, scope: !233)
!239 = !DILocation(line: 88, column: 41, scope: !233)
!240 = !DILocation(line: 88, column: 36, scope: !233)
!241 = !DILocation(line: 88, column: 47, scope: !233)
!242 = !DILocation(line: 88, column: 29, scope: !233)
!243 = !DILocation(line: 88, column: 11, scope: !233)
!244 = !DILocation(line: 88, column: 13, scope: !233)
!245 = !DILocation(line: 88, column: 5, scope: !233)
!246 = !DILocation(line: 88, column: 18, scope: !233)
!247 = !DILocation(line: 87, column: 51, scope: !248)
!248 = !DILexicalBlockFile(scope: !233, file: !1, discriminator: 2)
!249 = !DILocation(line: 87, column: 3, scope: !248)
!250 = !DILocation(line: 89, column: 8, scope: !109)
!251 = !DILocation(line: 89, column: 13, scope: !109)
!252 = !DILocation(line: 90, column: 8, scope: !109)
!253 = !DILocation(line: 90, column: 12, scope: !109)
!254 = !DILocation(line: 91, column: 7, scope: !109)
!255 = !DILocation(line: 91, column: 12, scope: !109)
!256 = !DILocation(line: 92, column: 7, scope: !109)
!257 = !DILocation(line: 92, column: 11, scope: !109)
!258 = !DILocation(line: 93, column: 10, scope: !259)
!259 = distinct !DILexicalBlock(scope: !109, file: !1, line: 93, column: 3)
!260 = !DILocation(line: 93, column: 8, scope: !259)
!261 = !DILocation(line: 93, column: 15, scope: !262)
!262 = !DILexicalBlockFile(scope: !263, file: !1, discriminator: 1)
!263 = distinct !DILexicalBlock(scope: !259, file: !1, line: 93, column: 3)
!264 = !DILocation(line: 93, column: 17, scope: !262)
!265 = !DILocation(line: 93, column: 3, scope: !262)
!266 = !DILocation(line: 94, column: 15, scope: !267)
!267 = distinct !DILexicalBlock(scope: !268, file: !1, line: 94, column: 9)
!268 = distinct !DILexicalBlock(scope: !263, file: !1, line: 93, column: 49)
!269 = !DILocation(line: 94, column: 9, scope: !267)
!270 = !DILocation(line: 94, column: 18, scope: !267)
!271 = !DILocation(line: 94, column: 9, scope: !268)
!272 = !DILocation(line: 95, column: 15, scope: !273)
!273 = distinct !DILexicalBlock(scope: !274, file: !1, line: 95, column: 11)
!274 = distinct !DILexicalBlock(scope: !267, file: !1, line: 94, column: 24)
!275 = !DILocation(line: 95, column: 20, scope: !273)
!276 = !DILocation(line: 95, column: 11, scope: !274)
!277 = !DILocation(line: 96, column: 20, scope: !273)
!278 = !DILocation(line: 96, column: 13, scope: !273)
!279 = !DILocation(line: 96, column: 18, scope: !273)
!280 = !DILocation(line: 96, column: 27, scope: !273)
!281 = !DILocation(line: 96, column: 31, scope: !273)
!282 = !DILocation(line: 96, column: 9, scope: !273)
!283 = !DILocation(line: 98, column: 13, scope: !273)
!284 = !DILocation(line: 98, column: 16, scope: !273)
!285 = !DILocation(line: 99, column: 5, scope: !274)
!286 = !DILocation(line: 100, column: 15, scope: !287)
!287 = distinct !DILexicalBlock(scope: !288, file: !1, line: 100, column: 11)
!288 = distinct !DILexicalBlock(scope: !267, file: !1, line: 99, column: 12)
!289 = !DILocation(line: 100, column: 20, scope: !287)
!290 = !DILocation(line: 100, column: 11, scope: !288)
!291 = !DILocation(line: 101, column: 18, scope: !292)
!292 = distinct !DILexicalBlock(scope: !293, file: !1, line: 101, column: 13)
!293 = distinct !DILexicalBlock(scope: !287, file: !1, line: 100, column: 27)
!294 = !DILocation(line: 101, column: 23, scope: !292)
!295 = !DILocation(line: 101, column: 29, scope: !292)
!296 = !DILocation(line: 101, column: 36, scope: !297)
!297 = !DILexicalBlockFile(scope: !292, file: !1, discriminator: 1)
!298 = !DILocation(line: 101, column: 47, scope: !297)
!299 = !DILocation(line: 101, column: 40, scope: !297)
!300 = !DILocation(line: 101, column: 13, scope: !297)
!301 = !DILocation(line: 102, column: 18, scope: !292)
!302 = !DILocation(line: 102, column: 11, scope: !292)
!303 = !DILocation(line: 103, column: 13, scope: !293)
!304 = !DILocation(line: 103, column: 18, scope: !293)
!305 = !DILocation(line: 104, column: 7, scope: !293)
!306 = !DILocation(line: 106, column: 3, scope: !268)
!307 = !DILocation(line: 93, column: 45, scope: !308)
!308 = !DILexicalBlockFile(scope: !263, file: !1, discriminator: 2)
!309 = !DILocation(line: 93, column: 3, scope: !308)
!310 = !DILocation(line: 107, column: 11, scope: !311)
!311 = distinct !DILexicalBlock(scope: !109, file: !1, line: 107, column: 7)
!312 = !DILocation(line: 107, column: 16, scope: !311)
!313 = !DILocation(line: 107, column: 7, scope: !109)
!314 = !DILocation(line: 108, column: 14, scope: !315)
!315 = distinct !DILexicalBlock(scope: !316, file: !1, line: 108, column: 9)
!316 = distinct !DILexicalBlock(scope: !311, file: !1, line: 107, column: 23)
!317 = !DILocation(line: 108, column: 19, scope: !315)
!318 = !DILocation(line: 108, column: 25, scope: !315)
!319 = !DILocation(line: 108, column: 32, scope: !320)
!320 = !DILexicalBlockFile(scope: !315, file: !1, discriminator: 1)
!321 = !DILocation(line: 108, column: 43, scope: !320)
!322 = !DILocation(line: 108, column: 36, scope: !320)
!323 = !DILocation(line: 108, column: 9, scope: !320)
!324 = !DILocation(line: 109, column: 14, scope: !315)
!325 = !DILocation(line: 109, column: 7, scope: !315)
!326 = !DILocation(line: 110, column: 3, scope: !316)
!327 = !DILocation(line: 111, column: 12, scope: !328)
!328 = distinct !DILexicalBlock(scope: !109, file: !1, line: 111, column: 7)
!329 = !DILocation(line: 111, column: 17, scope: !328)
!330 = !DILocation(line: 111, column: 23, scope: !328)
!331 = !DILocation(line: 111, column: 31, scope: !332)
!332 = !DILexicalBlockFile(scope: !328, file: !1, discriminator: 1)
!333 = !DILocation(line: 111, column: 35, scope: !332)
!334 = !DILocation(line: 111, column: 7, scope: !332)
!335 = !DILocation(line: 112, column: 10, scope: !328)
!336 = !DILocation(line: 112, column: 15, scope: !328)
!337 = !DILocation(line: 112, column: 5, scope: !328)
!338 = !DILocation(line: 117, column: 8, scope: !109)
!339 = !DILocation(line: 117, column: 6, scope: !109)
!340 = !DILocation(line: 118, column: 10, scope: !341)
!341 = distinct !DILexicalBlock(scope: !109, file: !1, line: 118, column: 3)
!342 = !DILocation(line: 118, column: 8, scope: !341)
!343 = !DILocation(line: 118, column: 15, scope: !344)
!344 = !DILexicalBlockFile(scope: !345, file: !1, discriminator: 1)
!345 = distinct !DILexicalBlock(scope: !341, file: !1, line: 118, column: 3)
!346 = !DILocation(line: 118, column: 17, scope: !344)
!347 = !DILocation(line: 118, column: 3, scope: !344)
!348 = !DILocation(line: 120, column: 14, scope: !349)
!349 = distinct !DILexicalBlock(scope: !350, file: !1, line: 120, column: 9)
!350 = distinct !DILexicalBlock(scope: !345, file: !1, line: 118, column: 49)
!351 = !DILocation(line: 120, column: 19, scope: !349)
!352 = !DILocation(line: 120, column: 25, scope: !349)
!353 = !DILocation(line: 120, column: 28, scope: !354)
!354 = !DILexicalBlockFile(scope: !349, file: !1, discriminator: 1)
!355 = !DILocation(line: 120, column: 38, scope: !354)
!356 = !DILocation(line: 120, column: 30, scope: !354)
!357 = !DILocation(line: 120, column: 43, scope: !354)
!358 = !DILocation(line: 121, column: 9, scope: !349)
!359 = !DILocation(line: 121, column: 19, scope: !349)
!360 = !DILocation(line: 121, column: 31, scope: !349)
!361 = !DILocation(line: 121, column: 24, scope: !349)
!362 = !DILocation(line: 121, column: 11, scope: !349)
!363 = !DILocation(line: 120, column: 9, scope: !364)
!364 = !DILexicalBlockFile(scope: !350, file: !1, discriminator: 2)
!365 = !DILocation(line: 122, column: 11, scope: !366)
!366 = distinct !DILexicalBlock(scope: !367, file: !1, line: 122, column: 11)
!367 = distinct !DILexicalBlock(scope: !349, file: !1, line: 121, column: 37)
!368 = !DILocation(line: 122, column: 21, scope: !366)
!369 = !DILocation(line: 122, column: 13, scope: !366)
!370 = !DILocation(line: 122, column: 11, scope: !367)
!371 = !DILocation(line: 123, column: 12, scope: !366)
!372 = !DILocation(line: 123, column: 15, scope: !366)
!373 = !DILocation(line: 123, column: 9, scope: !366)
!374 = !DILocation(line: 124, column: 7, scope: !367)
!375 = !DILocation(line: 127, column: 9, scope: !376)
!376 = distinct !DILexicalBlock(scope: !350, file: !1, line: 127, column: 9)
!377 = !DILocation(line: 127, column: 11, scope: !376)
!378 = !DILocation(line: 127, column: 9, scope: !350)
!379 = !DILocation(line: 128, column: 10, scope: !376)
!380 = !DILocation(line: 128, column: 13, scope: !376)
!381 = !DILocation(line: 128, column: 7, scope: !376)
!382 = !DILocation(line: 130, column: 9, scope: !383)
!383 = distinct !DILexicalBlock(scope: !350, file: !1, line: 130, column: 9)
!384 = !DILocation(line: 130, column: 11, scope: !383)
!385 = !DILocation(line: 130, column: 16, scope: !383)
!386 = !DILocation(line: 130, column: 24, scope: !387)
!387 = !DILexicalBlockFile(scope: !383, file: !1, discriminator: 1)
!388 = !DILocation(line: 130, column: 29, scope: !387)
!389 = !DILocation(line: 130, column: 34, scope: !387)
!390 = !DILocation(line: 130, column: 43, scope: !391)
!391 = !DILexicalBlockFile(scope: !383, file: !1, discriminator: 2)
!392 = !DILocation(line: 130, column: 47, scope: !391)
!393 = !DILocation(line: 130, column: 52, scope: !391)
!394 = !DILocation(line: 131, column: 15, scope: !383)
!395 = !DILocation(line: 131, column: 19, scope: !383)
!396 = !DILocation(line: 131, column: 24, scope: !383)
!397 = !DILocation(line: 131, column: 27, scope: !387)
!398 = !DILocation(line: 131, column: 36, scope: !387)
!399 = !DILocation(line: 131, column: 47, scope: !387)
!400 = !DILocation(line: 132, column: 15, scope: !383)
!401 = !DILocation(line: 132, column: 19, scope: !383)
!402 = !DILocation(line: 132, column: 24, scope: !383)
!403 = !DILocation(line: 132, column: 27, scope: !387)
!404 = !DILocation(line: 132, column: 36, scope: !387)
!405 = !DILocation(line: 130, column: 9, scope: !406)
!406 = !DILexicalBlockFile(scope: !350, file: !1, discriminator: 3)
!407 = !DILocalVariable(name: "err", scope: !408, file: !1, line: 133, type: !90)
!408 = distinct !DILexicalBlock(scope: !383, file: !1, line: 132, column: 49)
!409 = !DILocation(line: 133, column: 11, scope: !408)
!410 = !DILocation(line: 133, column: 28, scope: !408)
!411 = !DILocation(line: 133, column: 31, scope: !408)
!412 = !DILocation(line: 133, column: 36, scope: !408)
!413 = !DILocation(line: 133, column: 54, scope: !408)
!414 = !DILocation(line: 133, column: 59, scope: !408)
!415 = !DILocation(line: 133, column: 57, scope: !408)
!416 = !DILocation(line: 133, column: 51, scope: !408)
!417 = !DILocation(line: 133, column: 17, scope: !408)
!418 = !DILocation(line: 134, column: 11, scope: !419)
!419 = distinct !DILexicalBlock(scope: !408, file: !1, line: 134, column: 11)
!420 = !DILocation(line: 134, column: 11, scope: !408)
!421 = !DILocation(line: 135, column: 16, scope: !419)
!422 = !DILocation(line: 135, column: 9, scope: !419)
!423 = !DILocation(line: 136, column: 20, scope: !408)
!424 = !DILocation(line: 136, column: 13, scope: !408)
!425 = !DILocation(line: 136, column: 10, scope: !408)
!426 = !DILocation(line: 137, column: 7, scope: !408)
!427 = !DILocation(line: 139, column: 19, scope: !350)
!428 = !DILocation(line: 139, column: 35, scope: !350)
!429 = !DILocation(line: 139, column: 29, scope: !350)
!430 = !DILocation(line: 139, column: 11, scope: !350)
!431 = !DILocation(line: 139, column: 8, scope: !350)
!432 = !DILocation(line: 140, column: 3, scope: !350)
!433 = !DILocation(line: 118, column: 45, scope: !434)
!434 = !DILexicalBlockFile(scope: !345, file: !1, discriminator: 2)
!435 = !DILocation(line: 118, column: 3, scope: !434)
!436 = !DILocation(line: 142, column: 12, scope: !437)
!437 = distinct !DILexicalBlock(scope: !109, file: !1, line: 142, column: 7)
!438 = !DILocation(line: 142, column: 17, scope: !437)
!439 = !DILocation(line: 142, column: 23, scope: !437)
!440 = !DILocation(line: 142, column: 32, scope: !441)
!441 = !DILexicalBlockFile(scope: !437, file: !1, discriminator: 1)
!442 = !DILocation(line: 142, column: 44, scope: !441)
!443 = !DILocation(line: 142, column: 37, scope: !441)
!444 = !DILocation(line: 142, column: 26, scope: !441)
!445 = !DILocation(line: 142, column: 49, scope: !441)
!446 = !DILocation(line: 142, column: 7, scope: !441)
!447 = !DILocation(line: 143, column: 8, scope: !437)
!448 = !DILocation(line: 143, column: 11, scope: !437)
!449 = !DILocation(line: 143, column: 5, scope: !437)
!450 = !DILocation(line: 144, column: 6, scope: !109)
!451 = !DILocation(line: 144, column: 9, scope: !109)
!452 = !DILocation(line: 149, column: 16, scope: !453)
!453 = distinct !DILexicalBlock(scope: !109, file: !1, line: 149, column: 7)
!454 = !DILocation(line: 149, column: 21, scope: !453)
!455 = !DILocation(line: 149, column: 19, scope: !453)
!456 = !DILocation(line: 149, column: 28, scope: !453)
!457 = !DILocation(line: 149, column: 26, scope: !453)
!458 = !DILocation(line: 149, column: 7, scope: !109)
!459 = !DILocation(line: 150, column: 5, scope: !460)
!460 = distinct !DILexicalBlock(scope: !453, file: !1, line: 149, column: 34)
!461 = !DILocation(line: 152, column: 10, scope: !109)
!462 = !DILocation(line: 152, column: 15, scope: !109)
!463 = !DILocation(line: 152, column: 3, scope: !109)
!464 = !DILocation(line: 153, column: 3, scope: !109)
!465 = !DILocation(line: 154, column: 1, scope: !109)
!466 = !DILocalVariable(name: "af", arg: 1, scope: !99, file: !1, line: 157, type: !90)
!467 = !DILocation(line: 157, column: 22, scope: !99)
!468 = !DILocalVariable(name: "src", arg: 2, scope: !99, file: !1, line: 157, type: !102)
!469 = !DILocation(line: 157, column: 38, scope: !99)
!470 = !DILocalVariable(name: "dst", arg: 3, scope: !99, file: !1, line: 157, type: !84)
!471 = !DILocation(line: 157, column: 49, scope: !99)
!472 = !DILocation(line: 158, column: 7, scope: !473)
!473 = distinct !DILexicalBlock(scope: !99, file: !1, line: 158, column: 7)
!474 = !DILocation(line: 158, column: 11, scope: !473)
!475 = !DILocation(line: 158, column: 19, scope: !473)
!476 = !DILocation(line: 158, column: 22, scope: !477)
!477 = !DILexicalBlockFile(scope: !473, file: !1, discriminator: 1)
!478 = !DILocation(line: 158, column: 26, scope: !477)
!479 = !DILocation(line: 158, column: 7, scope: !477)
!480 = !DILocation(line: 159, column: 5, scope: !473)
!481 = !DILocation(line: 161, column: 11, scope: !99)
!482 = !DILocation(line: 161, column: 3, scope: !99)
!483 = !DILocation(line: 163, column: 24, scope: !484)
!484 = distinct !DILexicalBlock(scope: !99, file: !1, line: 161, column: 15)
!485 = !DILocation(line: 163, column: 29, scope: !484)
!486 = !DILocation(line: 163, column: 13, scope: !484)
!487 = !DILocation(line: 163, column: 5, scope: !484)
!488 = !DILocalVariable(name: "len", scope: !489, file: !1, line: 165, type: !90)
!489 = distinct !DILexicalBlock(scope: !484, file: !1, line: 164, column: 18)
!490 = !DILocation(line: 165, column: 9, scope: !489)
!491 = !DILocalVariable(name: "tmp", scope: !489, file: !1, line: 166, type: !205)
!492 = !DILocation(line: 166, column: 10, scope: !489)
!493 = !DILocalVariable(name: "s", scope: !489, file: !1, line: 166, type: !85)
!494 = !DILocation(line: 166, column: 38, scope: !489)
!495 = !DILocalVariable(name: "p", scope: !489, file: !1, line: 166, type: !85)
!496 = !DILocation(line: 166, column: 42, scope: !489)
!497 = !DILocation(line: 167, column: 17, scope: !489)
!498 = !DILocation(line: 167, column: 7, scope: !489)
!499 = !DILocation(line: 168, column: 16, scope: !489)
!500 = !DILocation(line: 168, column: 9, scope: !489)
!501 = !DILocation(line: 168, column: 7, scope: !489)
!502 = !DILocation(line: 169, column: 9, scope: !503)
!503 = distinct !DILexicalBlock(scope: !489, file: !1, line: 169, column: 9)
!504 = !DILocation(line: 169, column: 11, scope: !503)
!505 = !DILocation(line: 169, column: 9, scope: !489)
!506 = !DILocation(line: 170, column: 11, scope: !507)
!507 = distinct !DILexicalBlock(scope: !503, file: !1, line: 169, column: 20)
!508 = !DILocation(line: 170, column: 9, scope: !507)
!509 = !DILocation(line: 171, column: 13, scope: !507)
!510 = !DILocation(line: 171, column: 17, scope: !507)
!511 = !DILocation(line: 171, column: 15, scope: !507)
!512 = !DILocation(line: 171, column: 11, scope: !507)
!513 = !DILocation(line: 172, column: 11, scope: !514)
!514 = distinct !DILexicalBlock(scope: !507, file: !1, line: 172, column: 11)
!515 = !DILocation(line: 172, column: 15, scope: !514)
!516 = !DILocation(line: 172, column: 11, scope: !507)
!517 = !DILocation(line: 173, column: 9, scope: !514)
!518 = !DILocation(line: 174, column: 14, scope: !507)
!519 = !DILocation(line: 174, column: 17, scope: !507)
!520 = !DILocation(line: 174, column: 22, scope: !507)
!521 = !DILocation(line: 174, column: 7, scope: !507)
!522 = !DILocation(line: 175, column: 9, scope: !507)
!523 = !DILocation(line: 175, column: 7, scope: !507)
!524 = !DILocation(line: 175, column: 14, scope: !507)
!525 = !DILocation(line: 176, column: 5, scope: !507)
!526 = !DILocation(line: 177, column: 23, scope: !489)
!527 = !DILocation(line: 177, column: 26, scope: !489)
!528 = !DILocation(line: 177, column: 12, scope: !489)
!529 = !DILocation(line: 177, column: 5, scope: !489)
!530 = !DILocation(line: 180, column: 5, scope: !484)
!531 = !DILocation(line: 183, column: 1, scope: !99)
!532 = !DILocalVariable(name: "src", arg: 1, scope: !110, file: !1, line: 186, type: !102)
!533 = !DILocation(line: 186, column: 35, scope: !110)
!534 = !DILocalVariable(name: "dst", arg: 2, scope: !110, file: !1, line: 186, type: !113)
!535 = !DILocation(line: 186, column: 55, scope: !110)
!536 = !DILocalVariable(name: "saw_digit", scope: !110, file: !1, line: 188, type: !90)
!537 = !DILocation(line: 188, column: 7, scope: !110)
!538 = !DILocalVariable(name: "octets", scope: !110, file: !1, line: 188, type: !90)
!539 = !DILocation(line: 188, column: 18, scope: !110)
!540 = !DILocalVariable(name: "ch", scope: !110, file: !1, line: 188, type: !90)
!541 = !DILocation(line: 188, column: 26, scope: !110)
!542 = !DILocalVariable(name: "tmp", scope: !110, file: !1, line: 189, type: !543)
!543 = !DICompositeType(tag: DW_TAG_array_type, baseType: !91, size: 32, align: 8, elements: !544)
!544 = !{!545}
!545 = !DISubrange(count: 4)
!546 = !DILocation(line: 189, column: 17, scope: !110)
!547 = !DILocalVariable(name: "tp", scope: !110, file: !1, line: 189, type: !113)
!548 = !DILocation(line: 189, column: 47, scope: !110)
!549 = !DILocation(line: 191, column: 13, scope: !110)
!550 = !DILocation(line: 192, column: 10, scope: !110)
!551 = !DILocation(line: 193, column: 10, scope: !110)
!552 = !DILocation(line: 193, column: 8, scope: !110)
!553 = !DILocation(line: 193, column: 15, scope: !110)
!554 = !DILocation(line: 194, column: 3, scope: !110)
!555 = !DILocation(line: 194, column: 20, scope: !556)
!556 = !DILexicalBlockFile(scope: !110, file: !1, discriminator: 1)
!557 = !DILocation(line: 194, column: 16, scope: !556)
!558 = !DILocation(line: 194, column: 14, scope: !556)
!559 = !DILocation(line: 194, column: 24, scope: !556)
!560 = !DILocation(line: 194, column: 3, scope: !556)
!561 = !DILocalVariable(name: "pch", scope: !562, file: !1, line: 195, type: !102)
!562 = distinct !DILexicalBlock(scope: !110, file: !1, line: 194, column: 33)
!563 = !DILocation(line: 195, column: 17, scope: !562)
!564 = !DILocation(line: 197, column: 31, scope: !565)
!565 = distinct !DILexicalBlock(scope: !562, file: !1, line: 197, column: 9)
!566 = !DILocation(line: 197, column: 16, scope: !565)
!567 = !DILocation(line: 197, column: 14, scope: !565)
!568 = !DILocation(line: 197, column: 36, scope: !565)
!569 = !DILocation(line: 197, column: 9, scope: !562)
!570 = !DILocalVariable(name: "nw", scope: !571, file: !1, line: 198, type: !221)
!571 = distinct !DILexicalBlock(scope: !565, file: !1, line: 197, column: 45)
!572 = !DILocation(line: 198, column: 20, scope: !571)
!573 = !DILocation(line: 198, column: 26, scope: !571)
!574 = !DILocation(line: 198, column: 25, scope: !571)
!575 = !DILocation(line: 198, column: 29, scope: !571)
!576 = !DILocation(line: 198, column: 37, scope: !571)
!577 = !DILocation(line: 198, column: 41, scope: !571)
!578 = !DILocation(line: 198, column: 34, scope: !571)
!579 = !DILocation(line: 200, column: 11, scope: !580)
!580 = distinct !DILexicalBlock(scope: !571, file: !1, line: 200, column: 11)
!581 = !DILocation(line: 200, column: 21, scope: !580)
!582 = !DILocation(line: 200, column: 25, scope: !583)
!583 = !DILexicalBlockFile(scope: !580, file: !1, discriminator: 1)
!584 = !DILocation(line: 200, column: 24, scope: !583)
!585 = !DILocation(line: 200, column: 28, scope: !583)
!586 = !DILocation(line: 200, column: 11, scope: !583)
!587 = !DILocation(line: 201, column: 9, scope: !580)
!588 = !DILocation(line: 202, column: 11, scope: !589)
!589 = distinct !DILexicalBlock(scope: !571, file: !1, line: 202, column: 11)
!590 = !DILocation(line: 202, column: 14, scope: !589)
!591 = !DILocation(line: 202, column: 11, scope: !571)
!592 = !DILocation(line: 203, column: 9, scope: !589)
!593 = !DILocation(line: 204, column: 13, scope: !571)
!594 = !DILocation(line: 204, column: 8, scope: !571)
!595 = !DILocation(line: 204, column: 11, scope: !571)
!596 = !DILocation(line: 205, column: 12, scope: !597)
!597 = distinct !DILexicalBlock(scope: !571, file: !1, line: 205, column: 11)
!598 = !DILocation(line: 205, column: 11, scope: !571)
!599 = !DILocation(line: 206, column: 13, scope: !600)
!600 = distinct !DILexicalBlock(scope: !601, file: !1, line: 206, column: 13)
!601 = distinct !DILexicalBlock(scope: !597, file: !1, line: 205, column: 23)
!602 = !DILocation(line: 206, column: 22, scope: !600)
!603 = !DILocation(line: 206, column: 13, scope: !601)
!604 = !DILocation(line: 207, column: 11, scope: !600)
!605 = !DILocation(line: 208, column: 19, scope: !601)
!606 = !DILocation(line: 209, column: 7, scope: !601)
!607 = !DILocation(line: 210, column: 5, scope: !571)
!608 = !DILocation(line: 210, column: 16, scope: !609)
!609 = !DILexicalBlockFile(scope: !610, file: !1, discriminator: 1)
!610 = distinct !DILexicalBlock(scope: !565, file: !1, line: 210, column: 16)
!611 = !DILocation(line: 210, column: 19, scope: !609)
!612 = !DILocation(line: 210, column: 26, scope: !609)
!613 = !DILocation(line: 210, column: 29, scope: !614)
!614 = !DILexicalBlockFile(scope: !610, file: !1, discriminator: 2)
!615 = !DILocation(line: 210, column: 16, scope: !614)
!616 = !DILocation(line: 211, column: 11, scope: !617)
!617 = distinct !DILexicalBlock(scope: !618, file: !1, line: 211, column: 11)
!618 = distinct !DILexicalBlock(scope: !610, file: !1, line: 210, column: 40)
!619 = !DILocation(line: 211, column: 18, scope: !617)
!620 = !DILocation(line: 211, column: 11, scope: !618)
!621 = !DILocation(line: 212, column: 9, scope: !617)
!622 = !DILocation(line: 213, column: 8, scope: !618)
!623 = !DILocation(line: 213, column: 13, scope: !618)
!624 = !DILocation(line: 214, column: 17, scope: !618)
!625 = !DILocation(line: 215, column: 5, scope: !618)
!626 = !DILocation(line: 216, column: 7, scope: !610)
!627 = !DILocation(line: 194, column: 3, scope: !628)
!628 = !DILexicalBlockFile(scope: !110, file: !1, discriminator: 2)
!629 = !DILocation(line: 218, column: 7, scope: !630)
!630 = distinct !DILexicalBlock(scope: !110, file: !1, line: 218, column: 7)
!631 = !DILocation(line: 218, column: 14, scope: !630)
!632 = !DILocation(line: 218, column: 7, scope: !110)
!633 = !DILocation(line: 219, column: 5, scope: !630)
!634 = !DILocation(line: 220, column: 10, scope: !110)
!635 = !DILocation(line: 220, column: 3, scope: !110)
!636 = !DILocation(line: 221, column: 3, scope: !110)
!637 = !DILocation(line: 222, column: 1, scope: !110)
!638 = !DILocalVariable(name: "src", arg: 1, scope: !114, file: !1, line: 225, type: !102)
!639 = !DILocation(line: 225, column: 35, scope: !114)
!640 = !DILocalVariable(name: "dst", arg: 2, scope: !114, file: !1, line: 225, type: !113)
!641 = !DILocation(line: 225, column: 55, scope: !114)
!642 = !DILocalVariable(name: "tmp", scope: !114, file: !1, line: 228, type: !643)
!643 = !DICompositeType(tag: DW_TAG_array_type, baseType: !91, size: 128, align: 8, elements: !164)
!644 = !DILocation(line: 228, column: 17, scope: !114)
!645 = !DILocalVariable(name: "tp", scope: !114, file: !1, line: 228, type: !113)
!646 = !DILocation(line: 228, column: 48, scope: !114)
!647 = !DILocalVariable(name: "endp", scope: !114, file: !1, line: 228, type: !113)
!648 = !DILocation(line: 228, column: 53, scope: !114)
!649 = !DILocalVariable(name: "colonp", scope: !114, file: !1, line: 228, type: !113)
!650 = !DILocation(line: 228, column: 60, scope: !114)
!651 = !DILocalVariable(name: "xdigits", scope: !114, file: !1, line: 229, type: !102)
!652 = !DILocation(line: 229, column: 15, scope: !114)
!653 = !DILocalVariable(name: "curtok", scope: !114, file: !1, line: 229, type: !102)
!654 = !DILocation(line: 229, column: 25, scope: !114)
!655 = !DILocalVariable(name: "ch", scope: !114, file: !1, line: 230, type: !90)
!656 = !DILocation(line: 230, column: 7, scope: !114)
!657 = !DILocalVariable(name: "seen_xdigits", scope: !114, file: !1, line: 230, type: !90)
!658 = !DILocation(line: 230, column: 11, scope: !114)
!659 = !DILocalVariable(name: "val", scope: !114, file: !1, line: 231, type: !221)
!660 = !DILocation(line: 231, column: 16, scope: !114)
!661 = !DILocation(line: 233, column: 16, scope: !114)
!662 = !DILocation(line: 233, column: 14, scope: !114)
!663 = !DILocation(line: 233, column: 3, scope: !114)
!664 = !DILocation(line: 234, column: 10, scope: !114)
!665 = !DILocation(line: 234, column: 13, scope: !114)
!666 = !DILocation(line: 234, column: 8, scope: !114)
!667 = !DILocation(line: 235, column: 10, scope: !114)
!668 = !DILocation(line: 237, column: 8, scope: !669)
!669 = distinct !DILexicalBlock(scope: !114, file: !1, line: 237, column: 7)
!670 = !DILocation(line: 237, column: 7, scope: !669)
!671 = !DILocation(line: 237, column: 12, scope: !669)
!672 = !DILocation(line: 237, column: 7, scope: !114)
!673 = !DILocation(line: 238, column: 10, scope: !674)
!674 = distinct !DILexicalBlock(scope: !669, file: !1, line: 238, column: 9)
!675 = !DILocation(line: 238, column: 9, scope: !674)
!676 = !DILocation(line: 238, column: 16, scope: !674)
!677 = !DILocation(line: 238, column: 9, scope: !669)
!678 = !DILocation(line: 239, column: 7, scope: !674)
!679 = !DILocation(line: 238, column: 19, scope: !680)
!680 = !DILexicalBlockFile(scope: !674, file: !1, discriminator: 1)
!681 = !DILocation(line: 240, column: 12, scope: !114)
!682 = !DILocation(line: 240, column: 10, scope: !114)
!683 = !DILocation(line: 241, column: 16, scope: !114)
!684 = !DILocation(line: 242, column: 7, scope: !114)
!685 = !DILocation(line: 243, column: 3, scope: !114)
!686 = !DILocation(line: 243, column: 20, scope: !687)
!687 = !DILexicalBlockFile(scope: !114, file: !1, discriminator: 1)
!688 = !DILocation(line: 243, column: 16, scope: !687)
!689 = !DILocation(line: 243, column: 14, scope: !687)
!690 = !DILocation(line: 243, column: 24, scope: !687)
!691 = !DILocation(line: 243, column: 3, scope: !687)
!692 = !DILocalVariable(name: "pch", scope: !693, file: !1, line: 244, type: !102)
!693 = distinct !DILexicalBlock(scope: !114, file: !1, line: 243, column: 33)
!694 = !DILocation(line: 244, column: 17, scope: !693)
!695 = !DILocation(line: 246, column: 32, scope: !696)
!696 = distinct !DILexicalBlock(scope: !693, file: !1, line: 246, column: 9)
!697 = !DILocation(line: 246, column: 46, scope: !696)
!698 = !DILocation(line: 246, column: 16, scope: !696)
!699 = !DILocation(line: 246, column: 14, scope: !696)
!700 = !DILocation(line: 246, column: 51, scope: !696)
!701 = !DILocation(line: 246, column: 9, scope: !693)
!702 = !DILocation(line: 247, column: 29, scope: !696)
!703 = !DILocation(line: 247, column: 43, scope: !696)
!704 = !DILocation(line: 247, column: 13, scope: !696)
!705 = !DILocation(line: 247, column: 11, scope: !696)
!706 = !DILocation(line: 247, column: 7, scope: !696)
!707 = !DILocation(line: 248, column: 9, scope: !708)
!708 = distinct !DILexicalBlock(scope: !693, file: !1, line: 248, column: 9)
!709 = !DILocation(line: 248, column: 13, scope: !708)
!710 = !DILocation(line: 248, column: 9, scope: !693)
!711 = !DILocation(line: 249, column: 11, scope: !712)
!712 = distinct !DILexicalBlock(scope: !708, file: !1, line: 248, column: 22)
!713 = !DILocation(line: 250, column: 15, scope: !712)
!714 = !DILocation(line: 250, column: 21, scope: !712)
!715 = !DILocation(line: 250, column: 19, scope: !712)
!716 = !DILocation(line: 250, column: 11, scope: !712)
!717 = !DILocation(line: 251, column: 11, scope: !718)
!718 = distinct !DILexicalBlock(scope: !712, file: !1, line: 251, column: 11)
!719 = !DILocation(line: 251, column: 26, scope: !718)
!720 = !DILocation(line: 251, column: 11, scope: !712)
!721 = !DILocation(line: 252, column: 9, scope: !718)
!722 = !DILocation(line: 253, column: 7, scope: !712)
!723 = !DILocation(line: 255, column: 9, scope: !724)
!724 = distinct !DILexicalBlock(scope: !693, file: !1, line: 255, column: 9)
!725 = !DILocation(line: 255, column: 12, scope: !724)
!726 = !DILocation(line: 255, column: 9, scope: !693)
!727 = !DILocation(line: 256, column: 16, scope: !728)
!728 = distinct !DILexicalBlock(scope: !724, file: !1, line: 255, column: 20)
!729 = !DILocation(line: 256, column: 14, scope: !728)
!730 = !DILocation(line: 257, column: 12, scope: !731)
!731 = distinct !DILexicalBlock(scope: !728, file: !1, line: 257, column: 11)
!732 = !DILocation(line: 257, column: 11, scope: !728)
!733 = !DILocation(line: 258, column: 13, scope: !734)
!734 = distinct !DILexicalBlock(scope: !735, file: !1, line: 258, column: 13)
!735 = distinct !DILexicalBlock(scope: !731, file: !1, line: 257, column: 26)
!736 = !DILocation(line: 258, column: 13, scope: !735)
!737 = !DILocation(line: 259, column: 11, scope: !734)
!738 = !DILocation(line: 260, column: 18, scope: !735)
!739 = !DILocation(line: 260, column: 16, scope: !735)
!740 = !DILocation(line: 261, column: 9, scope: !735)
!741 = !DILocation(line: 262, column: 19, scope: !742)
!742 = distinct !DILexicalBlock(scope: !731, file: !1, line: 262, column: 18)
!743 = !DILocation(line: 262, column: 18, scope: !742)
!744 = !DILocation(line: 262, column: 23, scope: !742)
!745 = !DILocation(line: 262, column: 18, scope: !731)
!746 = !DILocation(line: 263, column: 9, scope: !747)
!747 = distinct !DILexicalBlock(scope: !742, file: !1, line: 262, column: 32)
!748 = !DILocation(line: 265, column: 11, scope: !749)
!749 = distinct !DILexicalBlock(scope: !728, file: !1, line: 265, column: 11)
!750 = !DILocation(line: 265, column: 14, scope: !749)
!751 = !DILocation(line: 265, column: 35, scope: !749)
!752 = !DILocation(line: 265, column: 33, scope: !749)
!753 = !DILocation(line: 265, column: 11, scope: !728)
!754 = !DILocation(line: 266, column: 9, scope: !749)
!755 = !DILocation(line: 267, column: 32, scope: !728)
!756 = !DILocation(line: 267, column: 36, scope: !728)
!757 = !DILocation(line: 267, column: 15, scope: !728)
!758 = !DILocation(line: 267, column: 42, scope: !728)
!759 = !DILocation(line: 267, column: 10, scope: !728)
!760 = !DILocation(line: 267, column: 13, scope: !728)
!761 = !DILocation(line: 268, column: 31, scope: !728)
!762 = !DILocation(line: 268, column: 15, scope: !728)
!763 = !DILocation(line: 268, column: 35, scope: !728)
!764 = !DILocation(line: 268, column: 10, scope: !728)
!765 = !DILocation(line: 268, column: 13, scope: !728)
!766 = !DILocation(line: 269, column: 20, scope: !728)
!767 = !DILocation(line: 270, column: 11, scope: !728)
!768 = !DILocation(line: 271, column: 7, scope: !728)
!769 = !DILocation(line: 273, column: 9, scope: !770)
!770 = distinct !DILexicalBlock(scope: !693, file: !1, line: 273, column: 9)
!771 = !DILocation(line: 273, column: 12, scope: !770)
!772 = !DILocation(line: 273, column: 19, scope: !770)
!773 = !DILocation(line: 273, column: 24, scope: !774)
!774 = !DILexicalBlockFile(scope: !770, file: !1, discriminator: 1)
!775 = !DILocation(line: 273, column: 27, scope: !774)
!776 = !DILocation(line: 273, column: 56, scope: !774)
!777 = !DILocation(line: 273, column: 53, scope: !774)
!778 = !DILocation(line: 273, column: 9, scope: !774)
!779 = !DILocalVariable(name: "err", scope: !780, file: !1, line: 274, type: !90)
!780 = distinct !DILexicalBlock(scope: !770, file: !1, line: 273, column: 63)
!781 = !DILocation(line: 274, column: 11, scope: !780)
!782 = !DILocation(line: 274, column: 28, scope: !780)
!783 = !DILocation(line: 274, column: 36, scope: !780)
!784 = !DILocation(line: 274, column: 17, scope: !780)
!785 = !DILocation(line: 275, column: 11, scope: !786)
!786 = distinct !DILexicalBlock(scope: !780, file: !1, line: 275, column: 11)
!787 = !DILocation(line: 275, column: 15, scope: !786)
!788 = !DILocation(line: 275, column: 11, scope: !780)
!789 = !DILocation(line: 276, column: 12, scope: !790)
!790 = distinct !DILexicalBlock(scope: !786, file: !1, line: 275, column: 21)
!791 = !DILocation(line: 277, column: 22, scope: !790)
!792 = !DILocation(line: 278, column: 9, scope: !790)
!793 = !DILocation(line: 280, column: 5, scope: !780)
!794 = !DILocation(line: 281, column: 5, scope: !693)
!795 = !DILocation(line: 283, column: 7, scope: !796)
!796 = distinct !DILexicalBlock(scope: !114, file: !1, line: 283, column: 7)
!797 = !DILocation(line: 283, column: 7, scope: !114)
!798 = !DILocation(line: 284, column: 9, scope: !799)
!799 = distinct !DILexicalBlock(scope: !800, file: !1, line: 284, column: 9)
!800 = distinct !DILexicalBlock(scope: !796, file: !1, line: 283, column: 21)
!801 = !DILocation(line: 284, column: 12, scope: !799)
!802 = !DILocation(line: 284, column: 33, scope: !799)
!803 = !DILocation(line: 284, column: 31, scope: !799)
!804 = !DILocation(line: 284, column: 9, scope: !800)
!805 = !DILocation(line: 285, column: 7, scope: !799)
!806 = !DILocation(line: 286, column: 30, scope: !800)
!807 = !DILocation(line: 286, column: 34, scope: !800)
!808 = !DILocation(line: 286, column: 13, scope: !800)
!809 = !DILocation(line: 286, column: 40, scope: !800)
!810 = !DILocation(line: 286, column: 8, scope: !800)
!811 = !DILocation(line: 286, column: 11, scope: !800)
!812 = !DILocation(line: 287, column: 29, scope: !800)
!813 = !DILocation(line: 287, column: 13, scope: !800)
!814 = !DILocation(line: 287, column: 33, scope: !800)
!815 = !DILocation(line: 287, column: 8, scope: !800)
!816 = !DILocation(line: 287, column: 11, scope: !800)
!817 = !DILocation(line: 288, column: 3, scope: !800)
!818 = !DILocation(line: 289, column: 7, scope: !819)
!819 = distinct !DILexicalBlock(scope: !114, file: !1, line: 289, column: 7)
!820 = !DILocation(line: 289, column: 14, scope: !819)
!821 = !DILocation(line: 289, column: 7, scope: !114)
!822 = !DILocalVariable(name: "n", scope: !823, file: !1, line: 294, type: !824)
!823 = distinct !DILexicalBlock(scope: !819, file: !1, line: 289, column: 23)
!824 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !90)
!825 = !DILocation(line: 294, column: 15, scope: !823)
!826 = !DILocation(line: 294, column: 19, scope: !823)
!827 = !DILocation(line: 294, column: 24, scope: !823)
!828 = !DILocation(line: 294, column: 22, scope: !823)
!829 = !DILocalVariable(name: "i", scope: !823, file: !1, line: 295, type: !90)
!830 = !DILocation(line: 295, column: 9, scope: !823)
!831 = !DILocation(line: 297, column: 9, scope: !832)
!832 = distinct !DILexicalBlock(scope: !823, file: !1, line: 297, column: 9)
!833 = !DILocation(line: 297, column: 15, scope: !832)
!834 = !DILocation(line: 297, column: 12, scope: !832)
!835 = !DILocation(line: 297, column: 9, scope: !823)
!836 = !DILocation(line: 298, column: 7, scope: !832)
!837 = !DILocation(line: 299, column: 12, scope: !838)
!838 = distinct !DILexicalBlock(scope: !823, file: !1, line: 299, column: 5)
!839 = !DILocation(line: 299, column: 10, scope: !838)
!840 = !DILocation(line: 299, column: 17, scope: !841)
!841 = !DILexicalBlockFile(scope: !842, file: !1, discriminator: 1)
!842 = distinct !DILexicalBlock(scope: !838, file: !1, line: 299, column: 5)
!843 = !DILocation(line: 299, column: 22, scope: !841)
!844 = !DILocation(line: 299, column: 19, scope: !841)
!845 = !DILocation(line: 299, column: 5, scope: !841)
!846 = !DILocation(line: 300, column: 26, scope: !847)
!847 = distinct !DILexicalBlock(scope: !842, file: !1, line: 299, column: 30)
!848 = !DILocation(line: 300, column: 30, scope: !847)
!849 = !DILocation(line: 300, column: 28, scope: !847)
!850 = !DILocation(line: 300, column: 19, scope: !847)
!851 = !DILocation(line: 300, column: 14, scope: !847)
!852 = !DILocation(line: 300, column: 12, scope: !847)
!853 = !DILocation(line: 300, column: 7, scope: !847)
!854 = !DILocation(line: 300, column: 17, scope: !847)
!855 = !DILocation(line: 301, column: 14, scope: !847)
!856 = !DILocation(line: 301, column: 18, scope: !847)
!857 = !DILocation(line: 301, column: 16, scope: !847)
!858 = !DILocation(line: 301, column: 7, scope: !847)
!859 = !DILocation(line: 301, column: 21, scope: !847)
!860 = !DILocation(line: 302, column: 5, scope: !847)
!861 = !DILocation(line: 299, column: 26, scope: !862)
!862 = !DILexicalBlockFile(scope: !842, file: !1, discriminator: 2)
!863 = !DILocation(line: 299, column: 5, scope: !862)
!864 = !DILocation(line: 303, column: 10, scope: !823)
!865 = !DILocation(line: 303, column: 8, scope: !823)
!866 = !DILocation(line: 304, column: 3, scope: !823)
!867 = !DILocation(line: 305, column: 7, scope: !868)
!868 = distinct !DILexicalBlock(scope: !114, file: !1, line: 305, column: 7)
!869 = !DILocation(line: 305, column: 13, scope: !868)
!870 = !DILocation(line: 305, column: 10, scope: !868)
!871 = !DILocation(line: 305, column: 7, scope: !114)
!872 = !DILocation(line: 306, column: 5, scope: !868)
!873 = !DILocation(line: 307, column: 10, scope: !114)
!874 = !DILocation(line: 307, column: 3, scope: !114)
!875 = !DILocation(line: 308, column: 3, scope: !114)
!876 = !DILocation(line: 309, column: 1, scope: !114)
