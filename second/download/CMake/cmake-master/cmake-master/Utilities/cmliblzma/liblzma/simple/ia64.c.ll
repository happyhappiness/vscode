; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/simple/ia64.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { %struct.lzma_next_coder_s, i8, i8, i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)*, %struct.lzma_simple_s*, i32, i64, i64, i64, i64, [0 x i8] }
%struct.lzma_simple_s = type opaque
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter_info_s = type { i64, {}*, i8* }

@ia64_code.BRANCH_TABLE = internal constant [32 x i32] [i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 4, i32 4, i32 6, i32 6, i32 0, i32 0, i32 7, i32 7, i32 4, i32 4, i32 0, i32 0, i32 4, i32 4, i32 0, i32 0], align 16

; Function Attrs: nounwind uwtable
define i32 @lzma_simple_ia64_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters) #0 !dbg !40 {
entry:
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !164, metadata !165), !dbg !166
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !167, metadata !165), !dbg !168
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !169, metadata !165), !dbg !170
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !171
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !172
  %2 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !173
  %call = call i32 @ia64_coder_init(%struct.lzma_next_coder_s* %0, %struct.lzma_allocator* %1, %struct.lzma_filter_info_s* %2, i1 zeroext true), !dbg !174
  ret i32 %call, !dbg !175
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i32 @ia64_coder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters, i1 zeroext %is_encoder) #0 !dbg !151 {
entry:
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  %is_encoder.addr = alloca i8, align 1
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !176, metadata !165), !dbg !177
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !178, metadata !165), !dbg !179
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !180, metadata !165), !dbg !181
  %frombool = zext i1 %is_encoder to i8
  store i8 %frombool, i8* %is_encoder.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %is_encoder.addr, metadata !182, metadata !165), !dbg !183
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !184
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !185
  %2 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !186
  %3 = load i8, i8* %is_encoder.addr, align 1, !dbg !187
  %tobool = trunc i8 %3 to i1, !dbg !187
  %call = call i32 @lzma_simple_coder_init(%struct.lzma_next_coder_s* %0, %struct.lzma_allocator* %1, %struct.lzma_filter_info_s* %2, i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)* @ia64_code, i64 0, i64 16, i32 16, i1 zeroext %tobool), !dbg !188
  ret i32 %call, !dbg !189
}

; Function Attrs: nounwind uwtable
define i32 @lzma_simple_ia64_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters) #0 !dbg !150 {
entry:
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !190, metadata !165), !dbg !191
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !192, metadata !165), !dbg !193
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !194, metadata !165), !dbg !195
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !196
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !197
  %2 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !198
  %call = call i32 @ia64_coder_init(%struct.lzma_next_coder_s* %0, %struct.lzma_allocator* %1, %struct.lzma_filter_info_s* %2, i1 zeroext false), !dbg !199
  ret i32 %call, !dbg !200
}

declare i32 @lzma_simple_coder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*, i64 (%struct.lzma_simple_s*, i32, i1, i8*, i64)*, i64, i64, i32, i1 zeroext) #2

; Function Attrs: nounwind uwtable
define internal i64 @ia64_code(%struct.lzma_simple_s* %simple, i32 %now_pos, i1 zeroext %is_encoder, i8* %buffer, i64 %size) #0 !dbg !154 {
entry:
  %simple.addr = alloca %struct.lzma_simple_s*, align 8
  %now_pos.addr = alloca i32, align 4
  %is_encoder.addr = alloca i8, align 1
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %i = alloca i64, align 8
  %slot = alloca i64, align 8
  %instr_template = alloca i32, align 4
  %mask = alloca i32, align 4
  %bit_pos = alloca i32, align 4
  %byte_pos = alloca i64, align 8
  %bit_res = alloca i32, align 4
  %instruction = alloca i64, align 8
  %inst_norm = alloca i64, align 8
  %j = alloca i64, align 8
  %dest = alloca i32, align 4
  %j32 = alloca i64, align 8
  %src = alloca i32, align 4
  store %struct.lzma_simple_s* %simple, %struct.lzma_simple_s** %simple.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_simple_s** %simple.addr, metadata !201, metadata !165), !dbg !202
  store i32 %now_pos, i32* %now_pos.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %now_pos.addr, metadata !203, metadata !165), !dbg !204
  %frombool = zext i1 %is_encoder to i8
  store i8 %frombool, i8* %is_encoder.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %is_encoder.addr, metadata !205, metadata !165), !dbg !206
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !207, metadata !165), !dbg !208
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !209, metadata !165), !dbg !210
  call void @llvm.dbg.declare(metadata i64* %i, metadata !211, metadata !165), !dbg !212
  store i64 0, i64* %i, align 8, !dbg !213
  br label %for.cond, !dbg !215

for.cond:                                         ; preds = %for.inc84, %entry
  %0 = load i64, i64* %i, align 8, !dbg !216
  %add = add i64 %0, 16, !dbg !219
  %1 = load i64, i64* %size.addr, align 8, !dbg !220
  %cmp = icmp ule i64 %add, %1, !dbg !221
  br i1 %cmp, label %for.body, label %for.end86, !dbg !222

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i64* %slot, metadata !223, metadata !165), !dbg !225
  call void @llvm.dbg.declare(metadata i32* %instr_template, metadata !226, metadata !165), !dbg !227
  %2 = load i64, i64* %i, align 8, !dbg !228
  %3 = load i8*, i8** %buffer.addr, align 8, !dbg !229
  %arrayidx = getelementptr inbounds i8, i8* %3, i64 %2, !dbg !229
  %4 = load i8, i8* %arrayidx, align 1, !dbg !229
  %conv = zext i8 %4 to i32, !dbg !229
  %and = and i32 %conv, 31, !dbg !230
  store i32 %and, i32* %instr_template, align 4, !dbg !227
  call void @llvm.dbg.declare(metadata i32* %mask, metadata !231, metadata !165), !dbg !232
  %5 = load i32, i32* %instr_template, align 4, !dbg !233
  %idxprom = zext i32 %5 to i64, !dbg !234
  %arrayidx1 = getelementptr inbounds [32 x i32], [32 x i32]* @ia64_code.BRANCH_TABLE, i64 0, i64 %idxprom, !dbg !234
  %6 = load i32, i32* %arrayidx1, align 4, !dbg !234
  store i32 %6, i32* %mask, align 4, !dbg !232
  call void @llvm.dbg.declare(metadata i32* %bit_pos, metadata !235, metadata !165), !dbg !236
  store i32 5, i32* %bit_pos, align 4, !dbg !236
  store i64 0, i64* %slot, align 8, !dbg !237
  br label %for.cond2, !dbg !239

for.cond2:                                        ; preds = %for.inc80, %for.body
  %7 = load i64, i64* %slot, align 8, !dbg !240
  %cmp3 = icmp ult i64 %7, 3, !dbg !243
  br i1 %cmp3, label %for.body5, label %for.end83, !dbg !244

for.body5:                                        ; preds = %for.cond2
  call void @llvm.dbg.declare(metadata i64* %byte_pos, metadata !245, metadata !165), !dbg !248
  %8 = load i32, i32* %bit_pos, align 4, !dbg !249
  %shr = lshr i32 %8, 3, !dbg !250
  %conv6 = zext i32 %shr to i64, !dbg !251
  store i64 %conv6, i64* %byte_pos, align 8, !dbg !248
  call void @llvm.dbg.declare(metadata i32* %bit_res, metadata !252, metadata !165), !dbg !253
  %9 = load i32, i32* %bit_pos, align 4, !dbg !254
  %and7 = and i32 %9, 7, !dbg !255
  store i32 %and7, i32* %bit_res, align 4, !dbg !253
  call void @llvm.dbg.declare(metadata i64* %instruction, metadata !256, metadata !165), !dbg !257
  store i64 0, i64* %instruction, align 8, !dbg !257
  call void @llvm.dbg.declare(metadata i64* %inst_norm, metadata !258, metadata !165), !dbg !259
  call void @llvm.dbg.declare(metadata i64* %j, metadata !260, metadata !165), !dbg !261
  %10 = load i32, i32* %mask, align 4, !dbg !262
  %11 = load i64, i64* %slot, align 8, !dbg !264
  %sh_prom = trunc i64 %11 to i32, !dbg !265
  %shr8 = lshr i32 %10, %sh_prom, !dbg !265
  %and9 = and i32 %shr8, 1, !dbg !266
  %cmp10 = icmp eq i32 %and9, 0, !dbg !267
  br i1 %cmp10, label %if.then, label %if.end, !dbg !268

if.then:                                          ; preds = %for.body5
  br label %for.inc80, !dbg !269

if.end:                                           ; preds = %for.body5
  store i64 0, i64* %j, align 8, !dbg !270
  br label %for.cond12, !dbg !272

for.cond12:                                       ; preds = %for.inc, %if.end
  %12 = load i64, i64* %j, align 8, !dbg !273
  %cmp13 = icmp ult i64 %12, 6, !dbg !276
  br i1 %cmp13, label %for.body15, label %for.end, !dbg !277

for.body15:                                       ; preds = %for.cond12
  %13 = load i64, i64* %i, align 8, !dbg !278
  %14 = load i64, i64* %j, align 8, !dbg !279
  %add16 = add i64 %13, %14, !dbg !280
  %15 = load i64, i64* %byte_pos, align 8, !dbg !281
  %add17 = add i64 %add16, %15, !dbg !282
  %16 = load i8*, i8** %buffer.addr, align 8, !dbg !283
  %arrayidx18 = getelementptr inbounds i8, i8* %16, i64 %add17, !dbg !283
  %17 = load i8, i8* %arrayidx18, align 1, !dbg !283
  %conv19 = zext i8 %17 to i64, !dbg !284
  %18 = load i64, i64* %j, align 8, !dbg !285
  %mul = mul i64 8, %18, !dbg !286
  %shl = shl i64 %conv19, %mul, !dbg !287
  %19 = load i64, i64* %instruction, align 8, !dbg !288
  %add20 = add i64 %19, %shl, !dbg !288
  store i64 %add20, i64* %instruction, align 8, !dbg !288
  br label %for.inc, !dbg !289

for.inc:                                          ; preds = %for.body15
  %20 = load i64, i64* %j, align 8, !dbg !290
  %inc = add i64 %20, 1, !dbg !290
  store i64 %inc, i64* %j, align 8, !dbg !290
  br label %for.cond12, !dbg !292

for.end:                                          ; preds = %for.cond12
  %21 = load i64, i64* %instruction, align 8, !dbg !293
  %22 = load i32, i32* %bit_res, align 4, !dbg !294
  %sh_prom21 = zext i32 %22 to i64, !dbg !295
  %shr22 = lshr i64 %21, %sh_prom21, !dbg !295
  store i64 %shr22, i64* %inst_norm, align 8, !dbg !296
  %23 = load i64, i64* %inst_norm, align 8, !dbg !297
  %shr23 = lshr i64 %23, 37, !dbg !299
  %and24 = and i64 %shr23, 15, !dbg !300
  %cmp25 = icmp eq i64 %and24, 5, !dbg !301
  br i1 %cmp25, label %land.lhs.true, label %if.end79, !dbg !302

land.lhs.true:                                    ; preds = %for.end
  %24 = load i64, i64* %inst_norm, align 8, !dbg !303
  %shr27 = lshr i64 %24, 9, !dbg !305
  %and28 = and i64 %shr27, 7, !dbg !306
  %cmp29 = icmp eq i64 %and28, 0, !dbg !307
  br i1 %cmp29, label %if.then31, label %if.end79, !dbg !308

if.then31:                                        ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i32* %dest, metadata !310, metadata !165), !dbg !312
  call void @llvm.dbg.declare(metadata i64* %j32, metadata !313, metadata !165), !dbg !314
  call void @llvm.dbg.declare(metadata i32* %src, metadata !315, metadata !165), !dbg !316
  %25 = load i64, i64* %inst_norm, align 8, !dbg !317
  %shr33 = lshr i64 %25, 13, !dbg !318
  %and34 = and i64 %shr33, 1048575, !dbg !319
  %conv35 = trunc i64 %and34 to i32, !dbg !320
  store i32 %conv35, i32* %src, align 4, !dbg !316
  %26 = load i64, i64* %inst_norm, align 8, !dbg !321
  %shr36 = lshr i64 %26, 36, !dbg !322
  %and37 = and i64 %shr36, 1, !dbg !323
  %shl38 = shl i64 %and37, 20, !dbg !324
  %27 = load i32, i32* %src, align 4, !dbg !325
  %conv39 = zext i32 %27 to i64, !dbg !325
  %or = or i64 %conv39, %shl38, !dbg !325
  %conv40 = trunc i64 %or to i32, !dbg !325
  store i32 %conv40, i32* %src, align 4, !dbg !325
  %28 = load i32, i32* %src, align 4, !dbg !326
  %shl41 = shl i32 %28, 4, !dbg !326
  store i32 %shl41, i32* %src, align 4, !dbg !326
  %29 = load i8, i8* %is_encoder.addr, align 1, !dbg !327
  %tobool = trunc i8 %29 to i1, !dbg !327
  br i1 %tobool, label %if.then42, label %if.else, !dbg !329

if.then42:                                        ; preds = %if.then31
  %30 = load i32, i32* %now_pos.addr, align 4, !dbg !330
  %31 = load i64, i64* %i, align 8, !dbg !331
  %conv43 = trunc i64 %31 to i32, !dbg !332
  %add44 = add i32 %30, %conv43, !dbg !333
  %32 = load i32, i32* %src, align 4, !dbg !334
  %add45 = add i32 %add44, %32, !dbg !335
  store i32 %add45, i32* %dest, align 4, !dbg !336
  br label %if.end48, !dbg !337

if.else:                                          ; preds = %if.then31
  %33 = load i32, i32* %src, align 4, !dbg !338
  %34 = load i32, i32* %now_pos.addr, align 4, !dbg !339
  %35 = load i64, i64* %i, align 8, !dbg !340
  %conv46 = trunc i64 %35 to i32, !dbg !341
  %add47 = add i32 %34, %conv46, !dbg !342
  %sub = sub i32 %33, %add47, !dbg !343
  store i32 %sub, i32* %dest, align 4, !dbg !344
  br label %if.end48

if.end48:                                         ; preds = %if.else, %if.then42
  %36 = load i32, i32* %dest, align 4, !dbg !345
  %shr49 = lshr i32 %36, 4, !dbg !345
  store i32 %shr49, i32* %dest, align 4, !dbg !345
  %37 = load i64, i64* %inst_norm, align 8, !dbg !346
  %and50 = and i64 %37, -77309403137, !dbg !346
  store i64 %and50, i64* %inst_norm, align 8, !dbg !346
  %38 = load i32, i32* %dest, align 4, !dbg !347
  %and51 = and i32 %38, 1048575, !dbg !348
  %conv52 = zext i32 %and51 to i64, !dbg !349
  %shl53 = shl i64 %conv52, 13, !dbg !350
  %39 = load i64, i64* %inst_norm, align 8, !dbg !351
  %or54 = or i64 %39, %shl53, !dbg !351
  store i64 %or54, i64* %inst_norm, align 8, !dbg !351
  %40 = load i32, i32* %dest, align 4, !dbg !352
  %and55 = and i32 %40, 1048576, !dbg !353
  %conv56 = zext i32 %and55 to i64, !dbg !354
  %shl57 = shl i64 %conv56, 16, !dbg !355
  %41 = load i64, i64* %inst_norm, align 8, !dbg !356
  %or58 = or i64 %41, %shl57, !dbg !356
  store i64 %or58, i64* %inst_norm, align 8, !dbg !356
  %42 = load i32, i32* %bit_res, align 4, !dbg !357
  %shl59 = shl i32 1, %42, !dbg !358
  %sub60 = sub nsw i32 %shl59, 1, !dbg !359
  %conv61 = sext i32 %sub60 to i64, !dbg !360
  %43 = load i64, i64* %instruction, align 8, !dbg !361
  %and62 = and i64 %43, %conv61, !dbg !361
  store i64 %and62, i64* %instruction, align 8, !dbg !361
  %44 = load i64, i64* %inst_norm, align 8, !dbg !362
  %45 = load i32, i32* %bit_res, align 4, !dbg !363
  %sh_prom63 = zext i32 %45 to i64, !dbg !364
  %shl64 = shl i64 %44, %sh_prom63, !dbg !364
  %46 = load i64, i64* %instruction, align 8, !dbg !365
  %or65 = or i64 %46, %shl64, !dbg !365
  store i64 %or65, i64* %instruction, align 8, !dbg !365
  store i64 0, i64* %j32, align 8, !dbg !366
  br label %for.cond66, !dbg !368

for.cond66:                                       ; preds = %for.inc76, %if.end48
  %47 = load i64, i64* %j32, align 8, !dbg !369
  %cmp67 = icmp ult i64 %47, 6, !dbg !372
  br i1 %cmp67, label %for.body69, label %for.end78, !dbg !373

for.body69:                                       ; preds = %for.cond66
  %48 = load i64, i64* %instruction, align 8, !dbg !374
  %49 = load i64, i64* %j32, align 8, !dbg !375
  %mul70 = mul i64 8, %49, !dbg !376
  %shr71 = lshr i64 %48, %mul70, !dbg !377
  %conv72 = trunc i64 %shr71 to i8, !dbg !378
  %50 = load i64, i64* %i, align 8, !dbg !379
  %51 = load i64, i64* %j32, align 8, !dbg !380
  %add73 = add i64 %50, %51, !dbg !381
  %52 = load i64, i64* %byte_pos, align 8, !dbg !382
  %add74 = add i64 %add73, %52, !dbg !383
  %53 = load i8*, i8** %buffer.addr, align 8, !dbg !384
  %arrayidx75 = getelementptr inbounds i8, i8* %53, i64 %add74, !dbg !384
  store i8 %conv72, i8* %arrayidx75, align 1, !dbg !385
  br label %for.inc76, !dbg !384

for.inc76:                                        ; preds = %for.body69
  %54 = load i64, i64* %j32, align 8, !dbg !386
  %inc77 = add i64 %54, 1, !dbg !386
  store i64 %inc77, i64* %j32, align 8, !dbg !386
  br label %for.cond66, !dbg !388

for.end78:                                        ; preds = %for.cond66
  br label %if.end79, !dbg !389

if.end79:                                         ; preds = %for.end78, %land.lhs.true, %for.end
  br label %for.inc80, !dbg !390

for.inc80:                                        ; preds = %if.end79, %if.then
  %55 = load i64, i64* %slot, align 8, !dbg !391
  %inc81 = add i64 %55, 1, !dbg !391
  store i64 %inc81, i64* %slot, align 8, !dbg !391
  %56 = load i32, i32* %bit_pos, align 4, !dbg !393
  %add82 = add i32 %56, 41, !dbg !393
  store i32 %add82, i32* %bit_pos, align 4, !dbg !393
  br label %for.cond2, !dbg !394

for.end83:                                        ; preds = %for.cond2
  br label %for.inc84, !dbg !395

for.inc84:                                        ; preds = %for.end83
  %57 = load i64, i64* %i, align 8, !dbg !396
  %add85 = add i64 %57, 16, !dbg !396
  store i64 %add85, i64* %i, align 8, !dbg !396
  br label %for.cond, !dbg !398

for.end86:                                        ; preds = %for.cond
  %58 = load i64, i64* %i, align 8, !dbg !399
  ret i64 %58, !dbg !400
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!161, !162}
!llvm.ident = !{!163}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !31, subprograms: !39, globals: !155)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/simple/ia64.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !24}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 57, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17}
!6 = !DIEnumerator(name: "LZMA_OK", value: 0)
!7 = !DIEnumerator(name: "LZMA_STREAM_END", value: 1)
!8 = !DIEnumerator(name: "LZMA_NO_CHECK", value: 2)
!9 = !DIEnumerator(name: "LZMA_UNSUPPORTED_CHECK", value: 3)
!10 = !DIEnumerator(name: "LZMA_GET_CHECK", value: 4)
!11 = !DIEnumerator(name: "LZMA_MEM_ERROR", value: 5)
!12 = !DIEnumerator(name: "LZMA_MEMLIMIT_ERROR", value: 6)
!13 = !DIEnumerator(name: "LZMA_FORMAT_ERROR", value: 7)
!14 = !DIEnumerator(name: "LZMA_OPTIONS_ERROR", value: 8)
!15 = !DIEnumerator(name: "LZMA_DATA_ERROR", value: 9)
!16 = !DIEnumerator(name: "LZMA_BUF_ERROR", value: 10)
!17 = !DIEnumerator(name: "LZMA_PROG_ERROR", value: 11)
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !19)
!19 = !{!20, !21, !22, !23}
!20 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!21 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!22 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!23 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!24 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !25, line: 27, size: 32, align: 32, elements: !26)
!25 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!26 = !{!27, !28, !29, !30}
!27 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!28 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!29 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!30 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!31 = !{!32, !35, !37}
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !33, line: 55, baseType: !34)
!33 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!34 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!35 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !33, line: 51, baseType: !36)
!36 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !33, line: 48, baseType: !38)
!38 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!39 = !{!40, !150, !151, !154}
!40 = distinct !DISubprogram(name: "lzma_simple_ia64_encoder_init", scope: !1, file: !1, line: 104, type: !41, isLocal: false, isDefinition: true, scopeLine: 106, flags: DIFlagPrototyped, isOptimized: false, variables: !149)
!41 = !DISubroutineType(types: !42)
!42 = !{!43, !44, !89, !139}
!43 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !46, line: 75, baseType: !47)
!46 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!47 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !46, line: 119, size: 512, align: 64, elements: !48)
!48 = !{!49, !79, !82, !84, !110, !115, !122, !127}
!49 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !47, file: !46, line: 121, baseType: !50, size: 64, align: 64)
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!51 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !46, line: 73, baseType: !52)
!52 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !53, line: 21, size: 1024, align: 64, elements: !54)
!53 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/simple/simple_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!54 = !{!55, !56, !58, !59, !69, !70, !71, !72, !73, !74, !75}
!55 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !52, file: !53, line: 23, baseType: !45, size: 512, align: 64)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "end_was_reached", scope: !52, file: !53, line: 26, baseType: !57, size: 8, align: 8, offset: 512)
!57 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "is_encoder", scope: !52, file: !53, line: 32, baseType: !57, size: 8, align: 8, offset: 520)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "filter", scope: !52, file: !53, line: 36, baseType: !60, size: 64, align: 64, offset: 576)
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DISubroutineType(types: !62)
!62 = !{!63, !65, !35, !57, !68, !63}
!63 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !64, line: 62, baseType: !34)
!64 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !66, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_simple", file: !53, line: 19, baseType: !67)
!67 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_simple_s", file: !53, line: 19, flags: DIFlagFwdDecl)
!68 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "simple", scope: !52, file: !53, line: 41, baseType: !65, size: 64, align: 64, offset: 640)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "now_pos", scope: !52, file: !53, line: 46, baseType: !35, size: 32, align: 32, offset: 704)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "allocated", scope: !52, file: !53, line: 49, baseType: !63, size: 64, align: 64, offset: 768)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !52, file: !53, line: 53, baseType: !63, size: 64, align: 64, offset: 832)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "filtered", scope: !52, file: !53, line: 57, baseType: !63, size: 64, align: 64, offset: 896)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !52, file: !53, line: 61, baseType: !63, size: 64, align: 64, offset: 960)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !52, file: !53, line: 64, baseType: !76, offset: 1024)
!76 = !DICompositeType(tag: DW_TAG_array_type, baseType: !37, align: 8, elements: !77)
!77 = !{!78}
!78 = !DISubrange(count: -1)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !47, file: !46, line: 125, baseType: !80, size: 64, align: 64, offset: 64)
!80 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !81, line: 63, baseType: !32)
!81 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!82 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !47, file: !46, line: 131, baseType: !83, size: 64, align: 64, offset: 128)
!83 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !33, line: 122, baseType: !34)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !47, file: !46, line: 134, baseType: !85, size: 64, align: 64, offset: 192)
!85 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !46, line: 89, baseType: !86)
!86 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !87, size: 64, align: 64)
!87 = !DISubroutineType(types: !88)
!88 = !{!43, !50, !89, !103, !106, !63, !108, !106, !63, !109}
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!90 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !91)
!91 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !92)
!92 = !{!93, !98, !102}
!93 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !91, file: !4, line: 376, baseType: !94, size: 64, align: 64)
!94 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !95, size: 64, align: 64)
!95 = !DISubroutineType(types: !96)
!96 = !{!97, !97, !63, !63}
!97 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !91, file: !4, line: 390, baseType: !99, size: 64, align: 64, offset: 64)
!99 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !100, size: 64, align: 64)
!100 = !DISubroutineType(types: !101)
!101 = !{null, !97, !97}
!102 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !91, file: !4, line: 401, baseType: !97, size: 64, align: 64, offset: 128)
!103 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !104)
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !37)
!106 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !107)
!107 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!108 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !68)
!109 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !18)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !47, file: !46, line: 139, baseType: !111, size: 64, align: 64, offset: 256)
!111 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !46, line: 97, baseType: !112)
!112 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !113, size: 64, align: 64)
!113 = !DISubroutineType(types: !114)
!114 = !{null, !50, !89}
!115 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !47, file: !46, line: 143, baseType: !116, size: 64, align: 64, offset: 320)
!116 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !117, size: 64, align: 64)
!117 = !DISubroutineType(types: !118)
!118 = !{!119, !120}
!119 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !25, line: 55, baseType: !24)
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !51)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !47, file: !46, line: 147, baseType: !123, size: 64, align: 64, offset: 384)
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !124, size: 64, align: 64)
!124 = !DISubroutineType(types: !125)
!125 = !{!43, !50, !126, !126, !32}
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !47, file: !46, line: 152, baseType: !128, size: 64, align: 64, offset: 448)
!128 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !129, size: 64, align: 64)
!129 = !DISubroutineType(types: !130)
!130 = !{!43, !50, !89, !131, !131}
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !133)
!133 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !134, line: 65, baseType: !135)
!134 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!135 = !DICompositeType(tag: DW_TAG_structure_type, file: !134, line: 43, size: 128, align: 64, elements: !136)
!136 = !{!137, !138}
!137 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !135, file: !134, line: 54, baseType: !80, size: 64, align: 64)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !135, file: !134, line: 63, baseType: !97, size: 64, align: 64, offset: 64)
!139 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !140, size: 64, align: 64)
!140 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !141)
!141 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !46, line: 77, baseType: !142)
!142 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !46, line: 104, size: 192, align: 64, elements: !143)
!143 = !{!144, !145, !148}
!144 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !142, file: !46, line: 107, baseType: !80, size: 64, align: 64)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !142, file: !46, line: 111, baseType: !146, size: 64, align: 64, offset: 64)
!146 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !46, line: 81, baseType: !147)
!147 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !142, file: !46, line: 114, baseType: !97, size: 64, align: 64, offset: 128)
!149 = !{}
!150 = distinct !DISubprogram(name: "lzma_simple_ia64_decoder_init", scope: !1, file: !1, line: 112, type: !41, isLocal: false, isDefinition: true, scopeLine: 114, flags: DIFlagPrototyped, isOptimized: false, variables: !149)
!151 = distinct !DISubprogram(name: "ia64_coder_init", scope: !1, file: !1, line: 95, type: !152, isLocal: true, isDefinition: true, scopeLine: 97, flags: DIFlagPrototyped, isOptimized: false, variables: !149)
!152 = !DISubroutineType(types: !153)
!153 = !{!43, !44, !89, !139, !57}
!154 = distinct !DISubprogram(name: "ia64_code", scope: !1, file: !1, line: 18, type: !61, isLocal: true, isDefinition: true, scopeLine: 21, flags: DIFlagPrototyped, isOptimized: false, variables: !149)
!155 = !{!156}
!156 = !DIGlobalVariable(name: "BRANCH_TABLE", scope: !154, file: !1, line: 22, type: !157, isLocal: true, isDefinition: true, variable: [32 x i32]* @ia64_code.BRANCH_TABLE)
!157 = !DICompositeType(tag: DW_TAG_array_type, baseType: !158, size: 1024, align: 32, elements: !159)
!158 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !35)
!159 = !{!160}
!160 = !DISubrange(count: 32)
!161 = !{i32 2, !"Dwarf Version", i32 4}
!162 = !{i32 2, !"Debug Info Version", i32 3}
!163 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!164 = !DILocalVariable(name: "next", arg: 1, scope: !40, file: !1, line: 104, type: !44)
!165 = !DIExpression()
!166 = !DILocation(line: 104, column: 48, scope: !40)
!167 = !DILocalVariable(name: "allocator", arg: 2, scope: !40, file: !1, line: 105, type: !89)
!168 = !DILocation(line: 105, column: 19, scope: !40)
!169 = !DILocalVariable(name: "filters", arg: 3, scope: !40, file: !1, line: 105, type: !139)
!170 = !DILocation(line: 105, column: 54, scope: !40)
!171 = !DILocation(line: 107, column: 25, scope: !40)
!172 = !DILocation(line: 107, column: 31, scope: !40)
!173 = !DILocation(line: 107, column: 42, scope: !40)
!174 = !DILocation(line: 107, column: 9, scope: !40)
!175 = !DILocation(line: 107, column: 2, scope: !40)
!176 = !DILocalVariable(name: "next", arg: 1, scope: !151, file: !1, line: 95, type: !44)
!177 = !DILocation(line: 95, column: 34, scope: !151)
!178 = !DILocalVariable(name: "allocator", arg: 2, scope: !151, file: !1, line: 95, type: !89)
!179 = !DILocation(line: 95, column: 56, scope: !151)
!180 = !DILocalVariable(name: "filters", arg: 3, scope: !151, file: !1, line: 96, type: !139)
!181 = !DILocation(line: 96, column: 27, scope: !151)
!182 = !DILocalVariable(name: "is_encoder", arg: 4, scope: !151, file: !1, line: 96, type: !57)
!183 = !DILocation(line: 96, column: 41, scope: !151)
!184 = !DILocation(line: 98, column: 32, scope: !151)
!185 = !DILocation(line: 98, column: 38, scope: !151)
!186 = !DILocation(line: 98, column: 49, scope: !151)
!187 = !DILocation(line: 99, column: 27, scope: !151)
!188 = !DILocation(line: 98, column: 9, scope: !151)
!189 = !DILocation(line: 98, column: 2, scope: !151)
!190 = !DILocalVariable(name: "next", arg: 1, scope: !150, file: !1, line: 112, type: !44)
!191 = !DILocation(line: 112, column: 48, scope: !150)
!192 = !DILocalVariable(name: "allocator", arg: 2, scope: !150, file: !1, line: 113, type: !89)
!193 = !DILocation(line: 113, column: 19, scope: !150)
!194 = !DILocalVariable(name: "filters", arg: 3, scope: !150, file: !1, line: 113, type: !139)
!195 = !DILocation(line: 113, column: 54, scope: !150)
!196 = !DILocation(line: 115, column: 25, scope: !150)
!197 = !DILocation(line: 115, column: 31, scope: !150)
!198 = !DILocation(line: 115, column: 42, scope: !150)
!199 = !DILocation(line: 115, column: 9, scope: !150)
!200 = !DILocation(line: 115, column: 2, scope: !150)
!201 = !DILocalVariable(name: "simple", arg: 1, scope: !154, file: !1, line: 18, type: !65)
!202 = !DILocation(line: 18, column: 24, scope: !154)
!203 = !DILocalVariable(name: "now_pos", arg: 2, scope: !154, file: !1, line: 19, type: !35)
!204 = !DILocation(line: 19, column: 12, scope: !154)
!205 = !DILocalVariable(name: "is_encoder", arg: 3, scope: !154, file: !1, line: 19, type: !57)
!206 = !DILocation(line: 19, column: 26, scope: !154)
!207 = !DILocalVariable(name: "buffer", arg: 4, scope: !154, file: !1, line: 20, type: !68)
!208 = !DILocation(line: 20, column: 12, scope: !154)
!209 = !DILocalVariable(name: "size", arg: 5, scope: !154, file: !1, line: 20, type: !63)
!210 = !DILocation(line: 20, column: 27, scope: !154)
!211 = !DILocalVariable(name: "i", scope: !154, file: !1, line: 29, type: !63)
!212 = !DILocation(line: 29, column: 9, scope: !154)
!213 = !DILocation(line: 30, column: 9, scope: !214)
!214 = distinct !DILexicalBlock(scope: !154, file: !1, line: 30, column: 2)
!215 = !DILocation(line: 30, column: 7, scope: !214)
!216 = !DILocation(line: 30, column: 14, scope: !217)
!217 = !DILexicalBlockFile(scope: !218, file: !1, discriminator: 1)
!218 = distinct !DILexicalBlock(scope: !214, file: !1, line: 30, column: 2)
!219 = !DILocation(line: 30, column: 16, scope: !217)
!220 = !DILocation(line: 30, column: 24, scope: !217)
!221 = !DILocation(line: 30, column: 21, scope: !217)
!222 = !DILocation(line: 30, column: 2, scope: !217)
!223 = !DILocalVariable(name: "slot", scope: !224, file: !1, line: 31, type: !63)
!224 = distinct !DILexicalBlock(scope: !218, file: !1, line: 30, column: 39)
!225 = !DILocation(line: 31, column: 10, scope: !224)
!226 = !DILocalVariable(name: "instr_template", scope: !224, file: !1, line: 33, type: !158)
!227 = !DILocation(line: 33, column: 18, scope: !224)
!228 = !DILocation(line: 33, column: 42, scope: !224)
!229 = !DILocation(line: 33, column: 35, scope: !224)
!230 = !DILocation(line: 33, column: 45, scope: !224)
!231 = !DILocalVariable(name: "mask", scope: !224, file: !1, line: 34, type: !158)
!232 = !DILocation(line: 34, column: 18, scope: !224)
!233 = !DILocation(line: 34, column: 38, scope: !224)
!234 = !DILocation(line: 34, column: 25, scope: !224)
!235 = !DILocalVariable(name: "bit_pos", scope: !224, file: !1, line: 35, type: !35)
!236 = !DILocation(line: 35, column: 12, scope: !224)
!237 = !DILocation(line: 37, column: 13, scope: !238)
!238 = distinct !DILexicalBlock(scope: !224, file: !1, line: 37, column: 3)
!239 = !DILocation(line: 37, column: 8, scope: !238)
!240 = !DILocation(line: 37, column: 18, scope: !241)
!241 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 1)
!242 = distinct !DILexicalBlock(scope: !238, file: !1, line: 37, column: 3)
!243 = !DILocation(line: 37, column: 23, scope: !241)
!244 = !DILocation(line: 37, column: 3, scope: !241)
!245 = !DILocalVariable(name: "byte_pos", scope: !246, file: !1, line: 38, type: !247)
!246 = distinct !DILexicalBlock(scope: !242, file: !1, line: 37, column: 51)
!247 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !63)
!248 = !DILocation(line: 38, column: 17, scope: !246)
!249 = !DILocation(line: 38, column: 29, scope: !246)
!250 = !DILocation(line: 38, column: 37, scope: !246)
!251 = !DILocation(line: 38, column: 28, scope: !246)
!252 = !DILocalVariable(name: "bit_res", scope: !246, file: !1, line: 39, type: !158)
!253 = !DILocation(line: 39, column: 19, scope: !246)
!254 = !DILocation(line: 39, column: 29, scope: !246)
!255 = !DILocation(line: 39, column: 37, scope: !246)
!256 = !DILocalVariable(name: "instruction", scope: !246, file: !1, line: 40, type: !32)
!257 = !DILocation(line: 40, column: 13, scope: !246)
!258 = !DILocalVariable(name: "inst_norm", scope: !246, file: !1, line: 41, type: !32)
!259 = !DILocation(line: 41, column: 13, scope: !246)
!260 = !DILocalVariable(name: "j", scope: !246, file: !1, line: 42, type: !63)
!261 = !DILocation(line: 42, column: 11, scope: !246)
!262 = !DILocation(line: 44, column: 10, scope: !263)
!263 = distinct !DILexicalBlock(scope: !246, file: !1, line: 44, column: 8)
!264 = !DILocation(line: 44, column: 18, scope: !263)
!265 = !DILocation(line: 44, column: 15, scope: !263)
!266 = !DILocation(line: 44, column: 24, scope: !263)
!267 = !DILocation(line: 44, column: 29, scope: !263)
!268 = !DILocation(line: 44, column: 8, scope: !246)
!269 = !DILocation(line: 45, column: 5, scope: !263)
!270 = !DILocation(line: 47, column: 11, scope: !271)
!271 = distinct !DILexicalBlock(scope: !246, file: !1, line: 47, column: 4)
!272 = !DILocation(line: 47, column: 9, scope: !271)
!273 = !DILocation(line: 47, column: 16, scope: !274)
!274 = !DILexicalBlockFile(scope: !275, file: !1, discriminator: 1)
!275 = distinct !DILexicalBlock(scope: !271, file: !1, line: 47, column: 4)
!276 = !DILocation(line: 47, column: 18, scope: !274)
!277 = !DILocation(line: 47, column: 4, scope: !274)
!278 = !DILocation(line: 49, column: 14, scope: !275)
!279 = !DILocation(line: 49, column: 18, scope: !275)
!280 = !DILocation(line: 49, column: 16, scope: !275)
!281 = !DILocation(line: 49, column: 22, scope: !275)
!282 = !DILocation(line: 49, column: 20, scope: !275)
!283 = !DILocation(line: 49, column: 7, scope: !275)
!284 = !DILocation(line: 48, column: 20, scope: !275)
!285 = !DILocation(line: 50, column: 15, scope: !275)
!286 = !DILocation(line: 50, column: 13, scope: !275)
!287 = !DILocation(line: 50, column: 7, scope: !275)
!288 = !DILocation(line: 48, column: 17, scope: !275)
!289 = !DILocation(line: 48, column: 5, scope: !275)
!290 = !DILocation(line: 47, column: 23, scope: !291)
!291 = !DILexicalBlockFile(scope: !275, file: !1, discriminator: 2)
!292 = !DILocation(line: 47, column: 4, scope: !291)
!293 = !DILocation(line: 52, column: 16, scope: !246)
!294 = !DILocation(line: 52, column: 31, scope: !246)
!295 = !DILocation(line: 52, column: 28, scope: !246)
!296 = !DILocation(line: 52, column: 14, scope: !246)
!297 = !DILocation(line: 54, column: 10, scope: !298)
!298 = distinct !DILexicalBlock(scope: !246, file: !1, line: 54, column: 8)
!299 = !DILocation(line: 54, column: 20, scope: !298)
!300 = !DILocation(line: 54, column: 27, scope: !298)
!301 = !DILocation(line: 54, column: 34, scope: !298)
!302 = !DILocation(line: 55, column: 6, scope: !298)
!303 = !DILocation(line: 55, column: 11, scope: !304)
!304 = !DILexicalBlockFile(scope: !298, file: !1, discriminator: 1)
!305 = !DILocation(line: 55, column: 21, scope: !304)
!306 = !DILocation(line: 55, column: 27, scope: !304)
!307 = !DILocation(line: 55, column: 34, scope: !304)
!308 = !DILocation(line: 54, column: 8, scope: !309)
!309 = !DILexicalBlockFile(scope: !246, file: !1, discriminator: 1)
!310 = !DILocalVariable(name: "dest", scope: !311, file: !1, line: 58, type: !35)
!311 = distinct !DILexicalBlock(scope: !298, file: !1, line: 57, column: 8)
!312 = !DILocation(line: 58, column: 14, scope: !311)
!313 = !DILocalVariable(name: "j", scope: !311, file: !1, line: 59, type: !63)
!314 = !DILocation(line: 59, column: 12, scope: !311)
!315 = !DILocalVariable(name: "src", scope: !311, file: !1, line: 61, type: !35)
!316 = !DILocation(line: 61, column: 14, scope: !311)
!317 = !DILocation(line: 62, column: 8, scope: !311)
!318 = !DILocation(line: 62, column: 18, scope: !311)
!319 = !DILocation(line: 62, column: 25, scope: !311)
!320 = !DILocation(line: 61, column: 20, scope: !311)
!321 = !DILocation(line: 63, column: 14, scope: !311)
!322 = !DILocation(line: 63, column: 24, scope: !311)
!323 = !DILocation(line: 63, column: 31, scope: !311)
!324 = !DILocation(line: 63, column: 36, scope: !311)
!325 = !DILocation(line: 63, column: 9, scope: !311)
!326 = !DILocation(line: 65, column: 9, scope: !311)
!327 = !DILocation(line: 67, column: 9, scope: !328)
!328 = distinct !DILexicalBlock(scope: !311, file: !1, line: 67, column: 9)
!329 = !DILocation(line: 67, column: 9, scope: !311)
!330 = !DILocation(line: 68, column: 13, scope: !328)
!331 = !DILocation(line: 68, column: 34, scope: !328)
!332 = !DILocation(line: 68, column: 23, scope: !328)
!333 = !DILocation(line: 68, column: 21, scope: !328)
!334 = !DILocation(line: 68, column: 39, scope: !328)
!335 = !DILocation(line: 68, column: 37, scope: !328)
!336 = !DILocation(line: 68, column: 11, scope: !328)
!337 = !DILocation(line: 68, column: 6, scope: !328)
!338 = !DILocation(line: 70, column: 13, scope: !328)
!339 = !DILocation(line: 70, column: 20, scope: !328)
!340 = !DILocation(line: 70, column: 41, scope: !328)
!341 = !DILocation(line: 70, column: 30, scope: !328)
!342 = !DILocation(line: 70, column: 28, scope: !328)
!343 = !DILocation(line: 70, column: 17, scope: !328)
!344 = !DILocation(line: 70, column: 11, scope: !328)
!345 = !DILocation(line: 72, column: 10, scope: !311)
!346 = !DILocation(line: 74, column: 15, scope: !311)
!347 = !DILocation(line: 75, column: 29, scope: !311)
!348 = !DILocation(line: 75, column: 34, scope: !311)
!349 = !DILocation(line: 75, column: 18, scope: !311)
!350 = !DILocation(line: 75, column: 45, scope: !311)
!351 = !DILocation(line: 75, column: 15, scope: !311)
!352 = !DILocation(line: 76, column: 29, scope: !311)
!353 = !DILocation(line: 76, column: 34, scope: !311)
!354 = !DILocation(line: 76, column: 18, scope: !311)
!355 = !DILocation(line: 77, column: 7, scope: !311)
!356 = !DILocation(line: 76, column: 15, scope: !311)
!357 = !DILocation(line: 79, column: 26, scope: !311)
!358 = !DILocation(line: 79, column: 23, scope: !311)
!359 = !DILocation(line: 79, column: 35, scope: !311)
!360 = !DILocation(line: 79, column: 20, scope: !311)
!361 = !DILocation(line: 79, column: 17, scope: !311)
!362 = !DILocation(line: 80, column: 21, scope: !311)
!363 = !DILocation(line: 80, column: 34, scope: !311)
!364 = !DILocation(line: 80, column: 31, scope: !311)
!365 = !DILocation(line: 80, column: 17, scope: !311)
!366 = !DILocation(line: 82, column: 12, scope: !367)
!367 = distinct !DILexicalBlock(scope: !311, file: !1, line: 82, column: 5)
!368 = !DILocation(line: 82, column: 10, scope: !367)
!369 = !DILocation(line: 82, column: 17, scope: !370)
!370 = !DILexicalBlockFile(scope: !371, file: !1, discriminator: 1)
!371 = distinct !DILexicalBlock(scope: !367, file: !1, line: 82, column: 5)
!372 = !DILocation(line: 82, column: 19, scope: !370)
!373 = !DILocation(line: 82, column: 5, scope: !370)
!374 = !DILocation(line: 84, column: 8, scope: !371)
!375 = !DILocation(line: 85, column: 16, scope: !371)
!376 = !DILocation(line: 85, column: 14, scope: !371)
!377 = !DILocation(line: 85, column: 8, scope: !371)
!378 = !DILocation(line: 83, column: 33, scope: !371)
!379 = !DILocation(line: 83, column: 13, scope: !371)
!380 = !DILocation(line: 83, column: 17, scope: !371)
!381 = !DILocation(line: 83, column: 15, scope: !371)
!382 = !DILocation(line: 83, column: 21, scope: !371)
!383 = !DILocation(line: 83, column: 19, scope: !371)
!384 = !DILocation(line: 83, column: 6, scope: !371)
!385 = !DILocation(line: 83, column: 31, scope: !371)
!386 = !DILocation(line: 82, column: 25, scope: !387)
!387 = !DILexicalBlockFile(scope: !371, file: !1, discriminator: 2)
!388 = !DILocation(line: 82, column: 5, scope: !387)
!389 = !DILocation(line: 86, column: 4, scope: !311)
!390 = !DILocation(line: 87, column: 3, scope: !246)
!391 = !DILocation(line: 37, column: 28, scope: !392)
!392 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 2)
!393 = !DILocation(line: 37, column: 44, scope: !392)
!394 = !DILocation(line: 37, column: 3, scope: !392)
!395 = !DILocation(line: 88, column: 2, scope: !224)
!396 = !DILocation(line: 30, column: 32, scope: !397)
!397 = !DILexicalBlockFile(scope: !218, file: !1, discriminator: 2)
!398 = !DILocation(line: 30, column: 2, scope: !397)
!399 = !DILocation(line: 90, column: 9, scope: !154)
!400 = !DILocation(line: 90, column: 2, scope: !154)
