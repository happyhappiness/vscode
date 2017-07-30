; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/sha1.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.sha1_ctx = type { [64 x i8], i64, [5 x i32] }

; Function Attrs: nounwind uwtable
define void @rhash_sha1_init(%struct.sha1_ctx* %ctx) #0 !dbg !10 {
entry:
  %ctx.addr = alloca %struct.sha1_ctx*, align 8
  store %struct.sha1_ctx* %ctx, %struct.sha1_ctx** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sha1_ctx** %ctx.addr, metadata !50, metadata !51), !dbg !52
  %0 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !53
  %length = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %0, i32 0, i32 1, !dbg !54
  store i64 0, i64* %length, align 8, !dbg !55
  %1 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !56
  %hash = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %1, i32 0, i32 2, !dbg !57
  %arrayidx = getelementptr inbounds [5 x i32], [5 x i32]* %hash, i64 0, i64 0, !dbg !56
  store i32 1732584193, i32* %arrayidx, align 8, !dbg !58
  %2 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !59
  %hash1 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %2, i32 0, i32 2, !dbg !60
  %arrayidx2 = getelementptr inbounds [5 x i32], [5 x i32]* %hash1, i64 0, i64 1, !dbg !59
  store i32 -271733879, i32* %arrayidx2, align 4, !dbg !61
  %3 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !62
  %hash3 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %3, i32 0, i32 2, !dbg !63
  %arrayidx4 = getelementptr inbounds [5 x i32], [5 x i32]* %hash3, i64 0, i64 2, !dbg !62
  store i32 -1732584194, i32* %arrayidx4, align 8, !dbg !64
  %4 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !65
  %hash5 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %4, i32 0, i32 2, !dbg !66
  %arrayidx6 = getelementptr inbounds [5 x i32], [5 x i32]* %hash5, i64 0, i64 3, !dbg !65
  store i32 271733878, i32* %arrayidx6, align 4, !dbg !67
  %5 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !68
  %hash7 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %5, i32 0, i32 2, !dbg !69
  %arrayidx8 = getelementptr inbounds [5 x i32], [5 x i32]* %hash7, i64 0, i64 4, !dbg !68
  store i32 -1009589776, i32* %arrayidx8, align 8, !dbg !70
  ret void, !dbg !71
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define void @rhash_sha1_update(%struct.sha1_ctx* %ctx, i8* %msg, i64 %size) #0 !dbg !31 {
entry:
  %ctx.addr = alloca %struct.sha1_ctx*, align 8
  %msg.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %index = alloca i32, align 4
  %left = alloca i32, align 4
  %aligned_message_block = alloca i32*, align 8
  store %struct.sha1_ctx* %ctx, %struct.sha1_ctx** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sha1_ctx** %ctx.addr, metadata !72, metadata !51), !dbg !73
  store i8* %msg, i8** %msg.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %msg.addr, metadata !74, metadata !51), !dbg !75
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !76, metadata !51), !dbg !77
  call void @llvm.dbg.declare(metadata i32* %index, metadata !78, metadata !51), !dbg !79
  %0 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !80
  %length = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %0, i32 0, i32 1, !dbg !81
  %1 = load i64, i64* %length, align 8, !dbg !81
  %conv = trunc i64 %1 to i32, !dbg !82
  %and = and i32 %conv, 63, !dbg !83
  store i32 %and, i32* %index, align 4, !dbg !79
  %2 = load i64, i64* %size.addr, align 8, !dbg !84
  %3 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !85
  %length1 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %3, i32 0, i32 1, !dbg !86
  %4 = load i64, i64* %length1, align 8, !dbg !87
  %add = add i64 %4, %2, !dbg !87
  store i64 %add, i64* %length1, align 8, !dbg !87
  %5 = load i32, i32* %index, align 4, !dbg !88
  %tobool = icmp ne i32 %5, 0, !dbg !88
  br i1 %tobool, label %if.then, label %if.end16, !dbg !90

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %left, metadata !91, metadata !51), !dbg !93
  %6 = load i32, i32* %index, align 4, !dbg !94
  %sub = sub i32 64, %6, !dbg !95
  store i32 %sub, i32* %left, align 4, !dbg !93
  %7 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !96
  %message = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %7, i32 0, i32 0, !dbg !97
  %arraydecay = getelementptr inbounds [64 x i8], [64 x i8]* %message, i32 0, i32 0, !dbg !96
  %8 = load i32, i32* %index, align 4, !dbg !98
  %idx.ext = zext i32 %8 to i64, !dbg !99
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay, i64 %idx.ext, !dbg !99
  %9 = load i8*, i8** %msg.addr, align 8, !dbg !100
  %10 = load i64, i64* %size.addr, align 8, !dbg !101
  %11 = load i32, i32* %left, align 4, !dbg !102
  %conv2 = zext i32 %11 to i64, !dbg !102
  %cmp = icmp ult i64 %10, %conv2, !dbg !103
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !101

cond.true:                                        ; preds = %if.then
  %12 = load i64, i64* %size.addr, align 8, !dbg !104
  br label %cond.end, !dbg !106

cond.false:                                       ; preds = %if.then
  %13 = load i32, i32* %left, align 4, !dbg !107
  %conv4 = zext i32 %13 to i64, !dbg !107
  br label %cond.end, !dbg !109

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %12, %cond.true ], [ %conv4, %cond.false ], !dbg !110
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %9, i64 %cond, i32 1, i1 false), !dbg !112
  %14 = load i64, i64* %size.addr, align 8, !dbg !113
  %15 = load i32, i32* %left, align 4, !dbg !115
  %conv5 = zext i32 %15 to i64, !dbg !115
  %cmp6 = icmp ult i64 %14, %conv5, !dbg !116
  br i1 %cmp6, label %if.then8, label %if.end, !dbg !117

if.then8:                                         ; preds = %cond.end
  br label %if.end36, !dbg !118

if.end:                                           ; preds = %cond.end
  %16 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !120
  %hash = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %16, i32 0, i32 2, !dbg !121
  %arraydecay9 = getelementptr inbounds [5 x i32], [5 x i32]* %hash, i32 0, i32 0, !dbg !120
  %17 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !122
  %message10 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %17, i32 0, i32 0, !dbg !123
  %arraydecay11 = getelementptr inbounds [64 x i8], [64 x i8]* %message10, i32 0, i32 0, !dbg !122
  %18 = bitcast i8* %arraydecay11 to i32*, !dbg !124
  call void @rhash_sha1_process_block(i32* %arraydecay9, i32* %18), !dbg !125
  %19 = load i32, i32* %left, align 4, !dbg !126
  %20 = load i8*, i8** %msg.addr, align 8, !dbg !127
  %idx.ext12 = zext i32 %19 to i64, !dbg !127
  %add.ptr13 = getelementptr inbounds i8, i8* %20, i64 %idx.ext12, !dbg !127
  store i8* %add.ptr13, i8** %msg.addr, align 8, !dbg !127
  %21 = load i32, i32* %left, align 4, !dbg !128
  %conv14 = zext i32 %21 to i64, !dbg !128
  %22 = load i64, i64* %size.addr, align 8, !dbg !129
  %sub15 = sub i64 %22, %conv14, !dbg !129
  store i64 %sub15, i64* %size.addr, align 8, !dbg !129
  br label %if.end16, !dbg !130

if.end16:                                         ; preds = %if.end, %entry
  br label %while.cond, !dbg !131

while.cond:                                       ; preds = %if.end27, %if.end16
  %23 = load i64, i64* %size.addr, align 8, !dbg !132
  %cmp17 = icmp uge i64 %23, 64, !dbg !134
  br i1 %cmp17, label %while.body, label %while.end, !dbg !135

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i32** %aligned_message_block, metadata !136, metadata !51), !dbg !138
  %24 = load i8*, i8** %msg.addr, align 8, !dbg !139
  %sub.ptr.lhs.cast = ptrtoint i8* %24 to i64, !dbg !139
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, 0, !dbg !139
  %and19 = and i64 3, %sub.ptr.sub, !dbg !139
  %cmp20 = icmp eq i64 0, %and19, !dbg !139
  br i1 %cmp20, label %if.then22, label %if.else, !dbg !141

if.then22:                                        ; preds = %while.body
  %25 = load i8*, i8** %msg.addr, align 8, !dbg !142
  %26 = bitcast i8* %25 to i32*, !dbg !144
  store i32* %26, i32** %aligned_message_block, align 8, !dbg !145
  br label %if.end27, !dbg !146

if.else:                                          ; preds = %while.body
  %27 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !147
  %message23 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %27, i32 0, i32 0, !dbg !149
  %arraydecay24 = getelementptr inbounds [64 x i8], [64 x i8]* %message23, i32 0, i32 0, !dbg !150
  %28 = load i8*, i8** %msg.addr, align 8, !dbg !151
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay24, i8* %28, i64 64, i32 1, i1 false), !dbg !150
  %29 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !152
  %message25 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %29, i32 0, i32 0, !dbg !153
  %arraydecay26 = getelementptr inbounds [64 x i8], [64 x i8]* %message25, i32 0, i32 0, !dbg !152
  %30 = bitcast i8* %arraydecay26 to i32*, !dbg !154
  store i32* %30, i32** %aligned_message_block, align 8, !dbg !155
  br label %if.end27

if.end27:                                         ; preds = %if.else, %if.then22
  %31 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !156
  %hash28 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %31, i32 0, i32 2, !dbg !157
  %arraydecay29 = getelementptr inbounds [5 x i32], [5 x i32]* %hash28, i32 0, i32 0, !dbg !156
  %32 = load i32*, i32** %aligned_message_block, align 8, !dbg !158
  call void @rhash_sha1_process_block(i32* %arraydecay29, i32* %32), !dbg !159
  %33 = load i8*, i8** %msg.addr, align 8, !dbg !160
  %add.ptr30 = getelementptr inbounds i8, i8* %33, i64 64, !dbg !160
  store i8* %add.ptr30, i8** %msg.addr, align 8, !dbg !160
  %34 = load i64, i64* %size.addr, align 8, !dbg !161
  %sub31 = sub i64 %34, 64, !dbg !161
  store i64 %sub31, i64* %size.addr, align 8, !dbg !161
  br label %while.cond, !dbg !162

while.end:                                        ; preds = %while.cond
  %35 = load i64, i64* %size.addr, align 8, !dbg !164
  %tobool32 = icmp ne i64 %35, 0, !dbg !164
  br i1 %tobool32, label %if.then33, label %if.end36, !dbg !166

if.then33:                                        ; preds = %while.end
  %36 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !167
  %message34 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %36, i32 0, i32 0, !dbg !169
  %arraydecay35 = getelementptr inbounds [64 x i8], [64 x i8]* %message34, i32 0, i32 0, !dbg !170
  %37 = load i8*, i8** %msg.addr, align 8, !dbg !171
  %38 = load i64, i64* %size.addr, align 8, !dbg !172
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay35, i8* %37, i64 %38, i32 1, i1 false), !dbg !170
  br label %if.end36, !dbg !173

if.end36:                                         ; preds = %if.then8, %if.then33, %while.end
  ret void, !dbg !174
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

; Function Attrs: nounwind uwtable
define internal void @rhash_sha1_process_block(i32* %hash, i32* %block) #0 !dbg !42 {
entry:
  %hash.addr = alloca i32*, align 8
  %block.addr = alloca i32*, align 8
  %t = alloca i32, align 4
  %temp = alloca i32, align 4
  %W = alloca [80 x i32], align 16
  %A = alloca i32, align 4
  %B = alloca i32, align 4
  %C = alloca i32, align 4
  %D = alloca i32, align 4
  %E = alloca i32, align 4
  store i32* %hash, i32** %hash.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %hash.addr, metadata !175, metadata !51), !dbg !176
  store i32* %block, i32** %block.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %block.addr, metadata !177, metadata !51), !dbg !178
  call void @llvm.dbg.declare(metadata i32* %t, metadata !179, metadata !51), !dbg !181
  call void @llvm.dbg.declare(metadata i32* %temp, metadata !182, metadata !51), !dbg !184
  call void @llvm.dbg.declare(metadata [80 x i32]* %W, metadata !185, metadata !51), !dbg !189
  call void @llvm.dbg.declare(metadata i32* %A, metadata !190, metadata !51), !dbg !191
  call void @llvm.dbg.declare(metadata i32* %B, metadata !192, metadata !51), !dbg !193
  call void @llvm.dbg.declare(metadata i32* %C, metadata !194, metadata !51), !dbg !195
  call void @llvm.dbg.declare(metadata i32* %D, metadata !196, metadata !51), !dbg !197
  call void @llvm.dbg.declare(metadata i32* %E, metadata !198, metadata !51), !dbg !199
  store i32 0, i32* %t, align 4, !dbg !200
  br label %for.cond, !dbg !202

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %t, align 4, !dbg !203
  %cmp = icmp slt i32 %0, 16, !dbg !206
  br i1 %cmp, label %for.body, label %for.end, !dbg !207

for.body:                                         ; preds = %for.cond
  %1 = load i32, i32* %t, align 4, !dbg !208
  %idxprom = sext i32 %1 to i64, !dbg !208
  %2 = load i32*, i32** %block.addr, align 8, !dbg !208
  %arrayidx = getelementptr inbounds i32, i32* %2, i64 %idxprom, !dbg !208
  %3 = load i32, i32* %arrayidx, align 4, !dbg !208
  %4 = call i32 @llvm.bswap.i32(i32 %3), !dbg !208
  %5 = load i32, i32* %t, align 4, !dbg !210
  %idxprom1 = sext i32 %5 to i64, !dbg !211
  %arrayidx2 = getelementptr inbounds [80 x i32], [80 x i32]* %W, i64 0, i64 %idxprom1, !dbg !211
  store i32 %4, i32* %arrayidx2, align 4, !dbg !212
  br label %for.inc, !dbg !213

for.inc:                                          ; preds = %for.body
  %6 = load i32, i32* %t, align 4, !dbg !214
  %inc = add nsw i32 %6, 1, !dbg !214
  store i32 %inc, i32* %t, align 4, !dbg !214
  br label %for.cond, !dbg !216

for.end:                                          ; preds = %for.cond
  store i32 16, i32* %t, align 4, !dbg !217
  br label %for.cond3, !dbg !219

for.cond3:                                        ; preds = %for.inc37, %for.end
  %7 = load i32, i32* %t, align 4, !dbg !220
  %cmp4 = icmp slt i32 %7, 80, !dbg !223
  br i1 %cmp4, label %for.body5, label %for.end39, !dbg !224

for.body5:                                        ; preds = %for.cond3
  %8 = load i32, i32* %t, align 4, !dbg !225
  %sub = sub nsw i32 %8, 3, !dbg !225
  %idxprom6 = sext i32 %sub to i64, !dbg !225
  %arrayidx7 = getelementptr inbounds [80 x i32], [80 x i32]* %W, i64 0, i64 %idxprom6, !dbg !225
  %9 = load i32, i32* %arrayidx7, align 4, !dbg !225
  %10 = load i32, i32* %t, align 4, !dbg !225
  %sub8 = sub nsw i32 %10, 8, !dbg !225
  %idxprom9 = sext i32 %sub8 to i64, !dbg !225
  %arrayidx10 = getelementptr inbounds [80 x i32], [80 x i32]* %W, i64 0, i64 %idxprom9, !dbg !225
  %11 = load i32, i32* %arrayidx10, align 4, !dbg !225
  %xor = xor i32 %9, %11, !dbg !225
  %12 = load i32, i32* %t, align 4, !dbg !225
  %sub11 = sub nsw i32 %12, 14, !dbg !225
  %idxprom12 = sext i32 %sub11 to i64, !dbg !225
  %arrayidx13 = getelementptr inbounds [80 x i32], [80 x i32]* %W, i64 0, i64 %idxprom12, !dbg !225
  %13 = load i32, i32* %arrayidx13, align 4, !dbg !225
  %xor14 = xor i32 %xor, %13, !dbg !225
  %14 = load i32, i32* %t, align 4, !dbg !225
  %sub15 = sub nsw i32 %14, 16, !dbg !225
  %idxprom16 = sext i32 %sub15 to i64, !dbg !225
  %arrayidx17 = getelementptr inbounds [80 x i32], [80 x i32]* %W, i64 0, i64 %idxprom16, !dbg !225
  %15 = load i32, i32* %arrayidx17, align 4, !dbg !225
  %xor18 = xor i32 %xor14, %15, !dbg !225
  %shl = shl i32 %xor18, 1, !dbg !225
  %16 = load i32, i32* %t, align 4, !dbg !225
  %sub19 = sub nsw i32 %16, 3, !dbg !225
  %idxprom20 = sext i32 %sub19 to i64, !dbg !225
  %arrayidx21 = getelementptr inbounds [80 x i32], [80 x i32]* %W, i64 0, i64 %idxprom20, !dbg !225
  %17 = load i32, i32* %arrayidx21, align 4, !dbg !225
  %18 = load i32, i32* %t, align 4, !dbg !225
  %sub22 = sub nsw i32 %18, 8, !dbg !225
  %idxprom23 = sext i32 %sub22 to i64, !dbg !225
  %arrayidx24 = getelementptr inbounds [80 x i32], [80 x i32]* %W, i64 0, i64 %idxprom23, !dbg !225
  %19 = load i32, i32* %arrayidx24, align 4, !dbg !225
  %xor25 = xor i32 %17, %19, !dbg !225
  %20 = load i32, i32* %t, align 4, !dbg !225
  %sub26 = sub nsw i32 %20, 14, !dbg !225
  %idxprom27 = sext i32 %sub26 to i64, !dbg !225
  %arrayidx28 = getelementptr inbounds [80 x i32], [80 x i32]* %W, i64 0, i64 %idxprom27, !dbg !225
  %21 = load i32, i32* %arrayidx28, align 4, !dbg !225
  %xor29 = xor i32 %xor25, %21, !dbg !225
  %22 = load i32, i32* %t, align 4, !dbg !225
  %sub30 = sub nsw i32 %22, 16, !dbg !225
  %idxprom31 = sext i32 %sub30 to i64, !dbg !225
  %arrayidx32 = getelementptr inbounds [80 x i32], [80 x i32]* %W, i64 0, i64 %idxprom31, !dbg !225
  %23 = load i32, i32* %arrayidx32, align 4, !dbg !225
  %xor33 = xor i32 %xor29, %23, !dbg !225
  %shr = lshr i32 %xor33, 31, !dbg !225
  %xor34 = xor i32 %shl, %shr, !dbg !225
  %24 = load i32, i32* %t, align 4, !dbg !227
  %idxprom35 = sext i32 %24 to i64, !dbg !228
  %arrayidx36 = getelementptr inbounds [80 x i32], [80 x i32]* %W, i64 0, i64 %idxprom35, !dbg !228
  store i32 %xor34, i32* %arrayidx36, align 4, !dbg !229
  br label %for.inc37, !dbg !230

for.inc37:                                        ; preds = %for.body5
  %25 = load i32, i32* %t, align 4, !dbg !231
  %inc38 = add nsw i32 %25, 1, !dbg !231
  store i32 %inc38, i32* %t, align 4, !dbg !231
  br label %for.cond3, !dbg !233

for.end39:                                        ; preds = %for.cond3
  %26 = load i32*, i32** %hash.addr, align 8, !dbg !234
  %arrayidx40 = getelementptr inbounds i32, i32* %26, i64 0, !dbg !234
  %27 = load i32, i32* %arrayidx40, align 4, !dbg !234
  store i32 %27, i32* %A, align 4, !dbg !235
  %28 = load i32*, i32** %hash.addr, align 8, !dbg !236
  %arrayidx41 = getelementptr inbounds i32, i32* %28, i64 1, !dbg !236
  %29 = load i32, i32* %arrayidx41, align 4, !dbg !236
  store i32 %29, i32* %B, align 4, !dbg !237
  %30 = load i32*, i32** %hash.addr, align 8, !dbg !238
  %arrayidx42 = getelementptr inbounds i32, i32* %30, i64 2, !dbg !238
  %31 = load i32, i32* %arrayidx42, align 4, !dbg !238
  store i32 %31, i32* %C, align 4, !dbg !239
  %32 = load i32*, i32** %hash.addr, align 8, !dbg !240
  %arrayidx43 = getelementptr inbounds i32, i32* %32, i64 3, !dbg !240
  %33 = load i32, i32* %arrayidx43, align 4, !dbg !240
  store i32 %33, i32* %D, align 4, !dbg !241
  %34 = load i32*, i32** %hash.addr, align 8, !dbg !242
  %arrayidx44 = getelementptr inbounds i32, i32* %34, i64 4, !dbg !242
  %35 = load i32, i32* %arrayidx44, align 4, !dbg !242
  store i32 %35, i32* %E, align 4, !dbg !243
  store i32 0, i32* %t, align 4, !dbg !244
  br label %for.cond45, !dbg !246

for.cond45:                                       ; preds = %for.inc61, %for.end39
  %36 = load i32, i32* %t, align 4, !dbg !247
  %cmp46 = icmp slt i32 %36, 20, !dbg !250
  br i1 %cmp46, label %for.body47, label %for.end63, !dbg !251

for.body47:                                       ; preds = %for.cond45
  %37 = load i32, i32* %A, align 4, !dbg !252
  %shl48 = shl i32 %37, 5, !dbg !252
  %38 = load i32, i32* %A, align 4, !dbg !252
  %shr49 = lshr i32 %38, 27, !dbg !252
  %xor50 = xor i32 %shl48, %shr49, !dbg !252
  %39 = load i32, i32* %C, align 4, !dbg !254
  %40 = load i32, i32* %D, align 4, !dbg !255
  %xor51 = xor i32 %39, %40, !dbg !256
  %41 = load i32, i32* %B, align 4, !dbg !257
  %and = and i32 %xor51, %41, !dbg !258
  %42 = load i32, i32* %D, align 4, !dbg !259
  %xor52 = xor i32 %and, %42, !dbg !260
  %add = add i32 %xor50, %xor52, !dbg !261
  %43 = load i32, i32* %E, align 4, !dbg !262
  %add53 = add i32 %add, %43, !dbg !263
  %44 = load i32, i32* %t, align 4, !dbg !264
  %idxprom54 = sext i32 %44 to i64, !dbg !265
  %arrayidx55 = getelementptr inbounds [80 x i32], [80 x i32]* %W, i64 0, i64 %idxprom54, !dbg !265
  %45 = load i32, i32* %arrayidx55, align 4, !dbg !265
  %add56 = add i32 %add53, %45, !dbg !266
  %add57 = add i32 %add56, 1518500249, !dbg !267
  store i32 %add57, i32* %temp, align 4, !dbg !268
  %46 = load i32, i32* %D, align 4, !dbg !269
  store i32 %46, i32* %E, align 4, !dbg !270
  %47 = load i32, i32* %C, align 4, !dbg !271
  store i32 %47, i32* %D, align 4, !dbg !272
  %48 = load i32, i32* %B, align 4, !dbg !273
  %shl58 = shl i32 %48, 30, !dbg !273
  %49 = load i32, i32* %B, align 4, !dbg !273
  %shr59 = lshr i32 %49, 2, !dbg !273
  %xor60 = xor i32 %shl58, %shr59, !dbg !273
  store i32 %xor60, i32* %C, align 4, !dbg !274
  %50 = load i32, i32* %A, align 4, !dbg !275
  store i32 %50, i32* %B, align 4, !dbg !276
  %51 = load i32, i32* %temp, align 4, !dbg !277
  store i32 %51, i32* %A, align 4, !dbg !278
  br label %for.inc61, !dbg !279

for.inc61:                                        ; preds = %for.body47
  %52 = load i32, i32* %t, align 4, !dbg !280
  %inc62 = add nsw i32 %52, 1, !dbg !280
  store i32 %inc62, i32* %t, align 4, !dbg !280
  br label %for.cond45, !dbg !282

for.end63:                                        ; preds = %for.cond45
  store i32 20, i32* %t, align 4, !dbg !283
  br label %for.cond64, !dbg !285

for.cond64:                                       ; preds = %for.inc81, %for.end63
  %53 = load i32, i32* %t, align 4, !dbg !286
  %cmp65 = icmp slt i32 %53, 40, !dbg !289
  br i1 %cmp65, label %for.body66, label %for.end83, !dbg !290

for.body66:                                       ; preds = %for.cond64
  %54 = load i32, i32* %A, align 4, !dbg !291
  %shl67 = shl i32 %54, 5, !dbg !291
  %55 = load i32, i32* %A, align 4, !dbg !291
  %shr68 = lshr i32 %55, 27, !dbg !291
  %xor69 = xor i32 %shl67, %shr68, !dbg !291
  %56 = load i32, i32* %B, align 4, !dbg !293
  %57 = load i32, i32* %C, align 4, !dbg !294
  %xor70 = xor i32 %56, %57, !dbg !295
  %58 = load i32, i32* %D, align 4, !dbg !296
  %xor71 = xor i32 %xor70, %58, !dbg !297
  %add72 = add i32 %xor69, %xor71, !dbg !298
  %59 = load i32, i32* %E, align 4, !dbg !299
  %add73 = add i32 %add72, %59, !dbg !300
  %60 = load i32, i32* %t, align 4, !dbg !301
  %idxprom74 = sext i32 %60 to i64, !dbg !302
  %arrayidx75 = getelementptr inbounds [80 x i32], [80 x i32]* %W, i64 0, i64 %idxprom74, !dbg !302
  %61 = load i32, i32* %arrayidx75, align 4, !dbg !302
  %add76 = add i32 %add73, %61, !dbg !303
  %add77 = add i32 %add76, 1859775393, !dbg !304
  store i32 %add77, i32* %temp, align 4, !dbg !305
  %62 = load i32, i32* %D, align 4, !dbg !306
  store i32 %62, i32* %E, align 4, !dbg !307
  %63 = load i32, i32* %C, align 4, !dbg !308
  store i32 %63, i32* %D, align 4, !dbg !309
  %64 = load i32, i32* %B, align 4, !dbg !310
  %shl78 = shl i32 %64, 30, !dbg !310
  %65 = load i32, i32* %B, align 4, !dbg !310
  %shr79 = lshr i32 %65, 2, !dbg !310
  %xor80 = xor i32 %shl78, %shr79, !dbg !310
  store i32 %xor80, i32* %C, align 4, !dbg !311
  %66 = load i32, i32* %A, align 4, !dbg !312
  store i32 %66, i32* %B, align 4, !dbg !313
  %67 = load i32, i32* %temp, align 4, !dbg !314
  store i32 %67, i32* %A, align 4, !dbg !315
  br label %for.inc81, !dbg !316

for.inc81:                                        ; preds = %for.body66
  %68 = load i32, i32* %t, align 4, !dbg !317
  %inc82 = add nsw i32 %68, 1, !dbg !317
  store i32 %inc82, i32* %t, align 4, !dbg !317
  br label %for.cond64, !dbg !319

for.end83:                                        ; preds = %for.cond64
  store i32 40, i32* %t, align 4, !dbg !320
  br label %for.cond84, !dbg !322

for.cond84:                                       ; preds = %for.inc103, %for.end83
  %69 = load i32, i32* %t, align 4, !dbg !323
  %cmp85 = icmp slt i32 %69, 60, !dbg !326
  br i1 %cmp85, label %for.body86, label %for.end105, !dbg !327

for.body86:                                       ; preds = %for.cond84
  %70 = load i32, i32* %A, align 4, !dbg !328
  %shl87 = shl i32 %70, 5, !dbg !328
  %71 = load i32, i32* %A, align 4, !dbg !328
  %shr88 = lshr i32 %71, 27, !dbg !328
  %xor89 = xor i32 %shl87, %shr88, !dbg !328
  %72 = load i32, i32* %B, align 4, !dbg !330
  %73 = load i32, i32* %C, align 4, !dbg !331
  %and90 = and i32 %72, %73, !dbg !332
  %74 = load i32, i32* %B, align 4, !dbg !333
  %75 = load i32, i32* %D, align 4, !dbg !334
  %and91 = and i32 %74, %75, !dbg !335
  %or = or i32 %and90, %and91, !dbg !336
  %76 = load i32, i32* %C, align 4, !dbg !337
  %77 = load i32, i32* %D, align 4, !dbg !338
  %and92 = and i32 %76, %77, !dbg !339
  %or93 = or i32 %or, %and92, !dbg !340
  %add94 = add i32 %xor89, %or93, !dbg !341
  %78 = load i32, i32* %E, align 4, !dbg !342
  %add95 = add i32 %add94, %78, !dbg !343
  %79 = load i32, i32* %t, align 4, !dbg !344
  %idxprom96 = sext i32 %79 to i64, !dbg !345
  %arrayidx97 = getelementptr inbounds [80 x i32], [80 x i32]* %W, i64 0, i64 %idxprom96, !dbg !345
  %80 = load i32, i32* %arrayidx97, align 4, !dbg !345
  %add98 = add i32 %add95, %80, !dbg !346
  %add99 = add i32 %add98, -1894007588, !dbg !347
  store i32 %add99, i32* %temp, align 4, !dbg !348
  %81 = load i32, i32* %D, align 4, !dbg !349
  store i32 %81, i32* %E, align 4, !dbg !350
  %82 = load i32, i32* %C, align 4, !dbg !351
  store i32 %82, i32* %D, align 4, !dbg !352
  %83 = load i32, i32* %B, align 4, !dbg !353
  %shl100 = shl i32 %83, 30, !dbg !353
  %84 = load i32, i32* %B, align 4, !dbg !353
  %shr101 = lshr i32 %84, 2, !dbg !353
  %xor102 = xor i32 %shl100, %shr101, !dbg !353
  store i32 %xor102, i32* %C, align 4, !dbg !354
  %85 = load i32, i32* %A, align 4, !dbg !355
  store i32 %85, i32* %B, align 4, !dbg !356
  %86 = load i32, i32* %temp, align 4, !dbg !357
  store i32 %86, i32* %A, align 4, !dbg !358
  br label %for.inc103, !dbg !359

for.inc103:                                       ; preds = %for.body86
  %87 = load i32, i32* %t, align 4, !dbg !360
  %inc104 = add nsw i32 %87, 1, !dbg !360
  store i32 %inc104, i32* %t, align 4, !dbg !360
  br label %for.cond84, !dbg !362

for.end105:                                       ; preds = %for.cond84
  store i32 60, i32* %t, align 4, !dbg !363
  br label %for.cond106, !dbg !365

for.cond106:                                      ; preds = %for.inc123, %for.end105
  %88 = load i32, i32* %t, align 4, !dbg !366
  %cmp107 = icmp slt i32 %88, 80, !dbg !369
  br i1 %cmp107, label %for.body108, label %for.end125, !dbg !370

for.body108:                                      ; preds = %for.cond106
  %89 = load i32, i32* %A, align 4, !dbg !371
  %shl109 = shl i32 %89, 5, !dbg !371
  %90 = load i32, i32* %A, align 4, !dbg !371
  %shr110 = lshr i32 %90, 27, !dbg !371
  %xor111 = xor i32 %shl109, %shr110, !dbg !371
  %91 = load i32, i32* %B, align 4, !dbg !373
  %92 = load i32, i32* %C, align 4, !dbg !374
  %xor112 = xor i32 %91, %92, !dbg !375
  %93 = load i32, i32* %D, align 4, !dbg !376
  %xor113 = xor i32 %xor112, %93, !dbg !377
  %add114 = add i32 %xor111, %xor113, !dbg !378
  %94 = load i32, i32* %E, align 4, !dbg !379
  %add115 = add i32 %add114, %94, !dbg !380
  %95 = load i32, i32* %t, align 4, !dbg !381
  %idxprom116 = sext i32 %95 to i64, !dbg !382
  %arrayidx117 = getelementptr inbounds [80 x i32], [80 x i32]* %W, i64 0, i64 %idxprom116, !dbg !382
  %96 = load i32, i32* %arrayidx117, align 4, !dbg !382
  %add118 = add i32 %add115, %96, !dbg !383
  %add119 = add i32 %add118, -899497514, !dbg !384
  store i32 %add119, i32* %temp, align 4, !dbg !385
  %97 = load i32, i32* %D, align 4, !dbg !386
  store i32 %97, i32* %E, align 4, !dbg !387
  %98 = load i32, i32* %C, align 4, !dbg !388
  store i32 %98, i32* %D, align 4, !dbg !389
  %99 = load i32, i32* %B, align 4, !dbg !390
  %shl120 = shl i32 %99, 30, !dbg !390
  %100 = load i32, i32* %B, align 4, !dbg !390
  %shr121 = lshr i32 %100, 2, !dbg !390
  %xor122 = xor i32 %shl120, %shr121, !dbg !390
  store i32 %xor122, i32* %C, align 4, !dbg !391
  %101 = load i32, i32* %A, align 4, !dbg !392
  store i32 %101, i32* %B, align 4, !dbg !393
  %102 = load i32, i32* %temp, align 4, !dbg !394
  store i32 %102, i32* %A, align 4, !dbg !395
  br label %for.inc123, !dbg !396

for.inc123:                                       ; preds = %for.body108
  %103 = load i32, i32* %t, align 4, !dbg !397
  %inc124 = add nsw i32 %103, 1, !dbg !397
  store i32 %inc124, i32* %t, align 4, !dbg !397
  br label %for.cond106, !dbg !399

for.end125:                                       ; preds = %for.cond106
  %104 = load i32, i32* %A, align 4, !dbg !400
  %105 = load i32*, i32** %hash.addr, align 8, !dbg !401
  %arrayidx126 = getelementptr inbounds i32, i32* %105, i64 0, !dbg !401
  %106 = load i32, i32* %arrayidx126, align 4, !dbg !402
  %add127 = add i32 %106, %104, !dbg !402
  store i32 %add127, i32* %arrayidx126, align 4, !dbg !402
  %107 = load i32, i32* %B, align 4, !dbg !403
  %108 = load i32*, i32** %hash.addr, align 8, !dbg !404
  %arrayidx128 = getelementptr inbounds i32, i32* %108, i64 1, !dbg !404
  %109 = load i32, i32* %arrayidx128, align 4, !dbg !405
  %add129 = add i32 %109, %107, !dbg !405
  store i32 %add129, i32* %arrayidx128, align 4, !dbg !405
  %110 = load i32, i32* %C, align 4, !dbg !406
  %111 = load i32*, i32** %hash.addr, align 8, !dbg !407
  %arrayidx130 = getelementptr inbounds i32, i32* %111, i64 2, !dbg !407
  %112 = load i32, i32* %arrayidx130, align 4, !dbg !408
  %add131 = add i32 %112, %110, !dbg !408
  store i32 %add131, i32* %arrayidx130, align 4, !dbg !408
  %113 = load i32, i32* %D, align 4, !dbg !409
  %114 = load i32*, i32** %hash.addr, align 8, !dbg !410
  %arrayidx132 = getelementptr inbounds i32, i32* %114, i64 3, !dbg !410
  %115 = load i32, i32* %arrayidx132, align 4, !dbg !411
  %add133 = add i32 %115, %113, !dbg !411
  store i32 %add133, i32* %arrayidx132, align 4, !dbg !411
  %116 = load i32, i32* %E, align 4, !dbg !412
  %117 = load i32*, i32** %hash.addr, align 8, !dbg !413
  %arrayidx134 = getelementptr inbounds i32, i32* %117, i64 4, !dbg !413
  %118 = load i32, i32* %arrayidx134, align 4, !dbg !414
  %add135 = add i32 %118, %116, !dbg !414
  store i32 %add135, i32* %arrayidx134, align 4, !dbg !414
  ret void, !dbg !415
}

; Function Attrs: nounwind uwtable
define void @rhash_sha1_final(%struct.sha1_ctx* %ctx, i8* %result) #0 !dbg !38 {
entry:
  %ctx.addr = alloca %struct.sha1_ctx*, align 8
  %result.addr = alloca i8*, align 8
  %index = alloca i32, align 4
  %msg32 = alloca i32*, align 8
  store %struct.sha1_ctx* %ctx, %struct.sha1_ctx** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sha1_ctx** %ctx.addr, metadata !416, metadata !51), !dbg !417
  store i8* %result, i8** %result.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %result.addr, metadata !418, metadata !51), !dbg !419
  call void @llvm.dbg.declare(metadata i32* %index, metadata !420, metadata !51), !dbg !421
  %0 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !422
  %length = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %0, i32 0, i32 1, !dbg !423
  %1 = load i64, i64* %length, align 8, !dbg !423
  %conv = trunc i64 %1 to i32, !dbg !424
  %and = and i32 %conv, 63, !dbg !425
  store i32 %and, i32* %index, align 4, !dbg !421
  call void @llvm.dbg.declare(metadata i32** %msg32, metadata !426, metadata !51), !dbg !427
  %2 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !428
  %message = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %2, i32 0, i32 0, !dbg !429
  %arraydecay = getelementptr inbounds [64 x i8], [64 x i8]* %message, i32 0, i32 0, !dbg !428
  %3 = bitcast i8* %arraydecay to i32*, !dbg !430
  store i32* %3, i32** %msg32, align 8, !dbg !427
  %4 = load i32, i32* %index, align 4, !dbg !431
  %inc = add i32 %4, 1, !dbg !431
  store i32 %inc, i32* %index, align 4, !dbg !431
  %idxprom = zext i32 %4 to i64, !dbg !432
  %5 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !432
  %message1 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %5, i32 0, i32 0, !dbg !433
  %arrayidx = getelementptr inbounds [64 x i8], [64 x i8]* %message1, i64 0, i64 %idxprom, !dbg !432
  store i8 -128, i8* %arrayidx, align 1, !dbg !434
  br label %while.cond, !dbg !435

while.cond:                                       ; preds = %while.body, %entry
  %6 = load i32, i32* %index, align 4, !dbg !436
  %and2 = and i32 %6, 3, !dbg !438
  %cmp = icmp ne i32 %and2, 0, !dbg !439
  br i1 %cmp, label %while.body, label %while.end, !dbg !440

while.body:                                       ; preds = %while.cond
  %7 = load i32, i32* %index, align 4, !dbg !441
  %inc4 = add i32 %7, 1, !dbg !441
  store i32 %inc4, i32* %index, align 4, !dbg !441
  %idxprom5 = zext i32 %7 to i64, !dbg !443
  %8 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !443
  %message6 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %8, i32 0, i32 0, !dbg !444
  %arrayidx7 = getelementptr inbounds [64 x i8], [64 x i8]* %message6, i64 0, i64 %idxprom5, !dbg !443
  store i8 0, i8* %arrayidx7, align 1, !dbg !445
  br label %while.cond, !dbg !446

while.end:                                        ; preds = %while.cond
  %9 = load i32, i32* %index, align 4, !dbg !448
  %shr = lshr i32 %9, 2, !dbg !448
  store i32 %shr, i32* %index, align 4, !dbg !448
  %10 = load i32, i32* %index, align 4, !dbg !449
  %cmp8 = icmp ugt i32 %10, 14, !dbg !451
  br i1 %cmp8, label %if.then, label %if.end, !dbg !452

if.then:                                          ; preds = %while.end
  br label %while.cond10, !dbg !453

while.cond10:                                     ; preds = %while.body13, %if.then
  %11 = load i32, i32* %index, align 4, !dbg !455
  %cmp11 = icmp ult i32 %11, 16, !dbg !457
  br i1 %cmp11, label %while.body13, label %while.end17, !dbg !458

while.body13:                                     ; preds = %while.cond10
  %12 = load i32, i32* %index, align 4, !dbg !459
  %inc14 = add i32 %12, 1, !dbg !459
  store i32 %inc14, i32* %index, align 4, !dbg !459
  %idxprom15 = zext i32 %12 to i64, !dbg !461
  %13 = load i32*, i32** %msg32, align 8, !dbg !461
  %arrayidx16 = getelementptr inbounds i32, i32* %13, i64 %idxprom15, !dbg !461
  store i32 0, i32* %arrayidx16, align 4, !dbg !462
  br label %while.cond10, !dbg !463

while.end17:                                      ; preds = %while.cond10
  %14 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !465
  %hash = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %14, i32 0, i32 2, !dbg !466
  %arraydecay18 = getelementptr inbounds [5 x i32], [5 x i32]* %hash, i32 0, i32 0, !dbg !465
  %15 = load i32*, i32** %msg32, align 8, !dbg !467
  call void @rhash_sha1_process_block(i32* %arraydecay18, i32* %15), !dbg !468
  store i32 0, i32* %index, align 4, !dbg !469
  br label %if.end, !dbg !470

if.end:                                           ; preds = %while.end17, %while.end
  br label %while.cond19, !dbg !471

while.cond19:                                     ; preds = %while.body22, %if.end
  %16 = load i32, i32* %index, align 4, !dbg !472
  %cmp20 = icmp ult i32 %16, 14, !dbg !473
  br i1 %cmp20, label %while.body22, label %while.end26, !dbg !474

while.body22:                                     ; preds = %while.cond19
  %17 = load i32, i32* %index, align 4, !dbg !475
  %inc23 = add i32 %17, 1, !dbg !475
  store i32 %inc23, i32* %index, align 4, !dbg !475
  %idxprom24 = zext i32 %17 to i64, !dbg !477
  %18 = load i32*, i32** %msg32, align 8, !dbg !477
  %arrayidx25 = getelementptr inbounds i32, i32* %18, i64 %idxprom24, !dbg !477
  store i32 0, i32* %arrayidx25, align 4, !dbg !478
  br label %while.cond19, !dbg !479

while.end26:                                      ; preds = %while.cond19
  %19 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !480
  %length27 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %19, i32 0, i32 1, !dbg !480
  %20 = load i64, i64* %length27, align 8, !dbg !480
  %shr28 = lshr i64 %20, 29, !dbg !480
  %conv29 = trunc i64 %shr28 to i32, !dbg !480
  %21 = call i32 @llvm.bswap.i32(i32 %conv29), !dbg !480
  %22 = load i32*, i32** %msg32, align 8, !dbg !481
  %arrayidx30 = getelementptr inbounds i32, i32* %22, i64 14, !dbg !481
  store i32 %21, i32* %arrayidx30, align 4, !dbg !482
  %23 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !483
  %length31 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %23, i32 0, i32 1, !dbg !483
  %24 = load i64, i64* %length31, align 8, !dbg !483
  %shl = shl i64 %24, 3, !dbg !483
  %conv32 = trunc i64 %shl to i32, !dbg !483
  %25 = call i32 @llvm.bswap.i32(i32 %conv32), !dbg !483
  %26 = load i32*, i32** %msg32, align 8, !dbg !484
  %arrayidx33 = getelementptr inbounds i32, i32* %26, i64 15, !dbg !484
  store i32 %25, i32* %arrayidx33, align 4, !dbg !485
  %27 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !486
  %hash34 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %27, i32 0, i32 2, !dbg !487
  %arraydecay35 = getelementptr inbounds [5 x i32], [5 x i32]* %hash34, i32 0, i32 0, !dbg !486
  %28 = load i32*, i32** %msg32, align 8, !dbg !488
  call void @rhash_sha1_process_block(i32* %arraydecay35, i32* %28), !dbg !489
  %29 = load i8*, i8** %result.addr, align 8, !dbg !490
  %tobool = icmp ne i8* %29, null, !dbg !490
  br i1 %tobool, label %if.then36, label %if.end38, !dbg !492

if.then36:                                        ; preds = %while.end26
  %30 = load i8*, i8** %result.addr, align 8, !dbg !493
  %31 = load %struct.sha1_ctx*, %struct.sha1_ctx** %ctx.addr, align 8, !dbg !493
  %hash37 = getelementptr inbounds %struct.sha1_ctx, %struct.sha1_ctx* %31, i32 0, i32 2, !dbg !493
  %32 = bitcast [5 x i32]* %hash37 to i8*, !dbg !493
  call void @rhash_swap_copy_str_to_u32(i8* %30, i32 0, i8* %32, i64 20), !dbg !493
  br label %if.end38, !dbg !493

if.end38:                                         ; preds = %if.then36, %while.end26
  ret void, !dbg !495
}

; Function Attrs: nounwind readnone
declare i32 @llvm.bswap.i32(i32) #1

declare void @rhash_swap_copy_str_to_u32(i8*, i32, i8*, i64) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { argmemonly nounwind }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!47, !48}
!llvm.ident = !{!49}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !9)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/sha1.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!2 = !{}
!3 = !{!4, !5, !6}
!4 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64, align: 64)
!6 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64, align: 64)
!7 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !8)
!8 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!9 = !{!10, !31, !38, !42}
!10 = distinct !DISubprogram(name: "rhash_sha1_init", scope: !1, file: !1, line: 27, type: !11, isLocal: false, isDefinition: true, scopeLine: 28, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!11 = !DISubroutineType(types: !12)
!12 = !{null, !13}
!13 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !14, size: 64, align: 64)
!14 = !DIDerivedType(tag: DW_TAG_typedef, name: "sha1_ctx", file: !15, line: 19, baseType: !16)
!15 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/sha1.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!16 = !DICompositeType(tag: DW_TAG_structure_type, name: "sha1_ctx", file: !15, line: 14, size: 768, align: 64, elements: !17)
!17 = !{!18, !23, !27}
!18 = !DIDerivedType(tag: DW_TAG_member, name: "message", scope: !16, file: !15, line: 16, baseType: !19, size: 512, align: 8)
!19 = !DICompositeType(tag: DW_TAG_array_type, baseType: !20, size: 512, align: 8, elements: !21)
!20 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!21 = !{!22}
!22 = !DISubrange(count: 64)
!23 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !16, file: !15, line: 17, baseType: !24, size: 64, align: 64, offset: 512)
!24 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !25, line: 55, baseType: !26)
!25 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!26 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!27 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !16, file: !15, line: 18, baseType: !28, size: 160, align: 32, offset: 576)
!28 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 160, align: 32, elements: !29)
!29 = !{!30}
!30 = !DISubrange(count: 5)
!31 = distinct !DISubprogram(name: "rhash_sha1_update", scope: !1, file: !1, line: 124, type: !32, isLocal: false, isDefinition: true, scopeLine: 125, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!32 = !DISubroutineType(types: !33)
!33 = !{null, !13, !34, !36}
!34 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!35 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !20)
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !37, line: 62, baseType: !26)
!37 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!38 = distinct !DISubprogram(name: "rhash_sha1_final", scope: !1, file: !1, line: 167, type: !39, isLocal: false, isDefinition: true, scopeLine: 168, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!39 = !DISubroutineType(types: !40)
!40 = !{null, !13, !41}
!41 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64, align: 64)
!42 = distinct !DISubprogram(name: "rhash_sha1_process_block", scope: !1, file: !1, line: 46, type: !43, isLocal: true, isDefinition: true, scopeLine: 47, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!43 = !DISubroutineType(types: !44)
!44 = !{null, !5, !45}
!45 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !46, size: 64, align: 64)
!46 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !4)
!47 = !{i32 2, !"Dwarf Version", i32 4}
!48 = !{i32 2, !"Debug Info Version", i32 3}
!49 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!50 = !DILocalVariable(name: "ctx", arg: 1, scope: !10, file: !1, line: 27, type: !13)
!51 = !DIExpression()
!52 = !DILocation(line: 27, column: 32, scope: !10)
!53 = !DILocation(line: 29, column: 2, scope: !10)
!54 = !DILocation(line: 29, column: 7, scope: !10)
!55 = !DILocation(line: 29, column: 14, scope: !10)
!56 = !DILocation(line: 32, column: 2, scope: !10)
!57 = !DILocation(line: 32, column: 7, scope: !10)
!58 = !DILocation(line: 32, column: 15, scope: !10)
!59 = !DILocation(line: 33, column: 2, scope: !10)
!60 = !DILocation(line: 33, column: 7, scope: !10)
!61 = !DILocation(line: 33, column: 15, scope: !10)
!62 = !DILocation(line: 34, column: 2, scope: !10)
!63 = !DILocation(line: 34, column: 7, scope: !10)
!64 = !DILocation(line: 34, column: 15, scope: !10)
!65 = !DILocation(line: 35, column: 2, scope: !10)
!66 = !DILocation(line: 35, column: 7, scope: !10)
!67 = !DILocation(line: 35, column: 15, scope: !10)
!68 = !DILocation(line: 36, column: 2, scope: !10)
!69 = !DILocation(line: 36, column: 7, scope: !10)
!70 = !DILocation(line: 36, column: 15, scope: !10)
!71 = !DILocation(line: 37, column: 1, scope: !10)
!72 = !DILocalVariable(name: "ctx", arg: 1, scope: !31, file: !1, line: 124, type: !13)
!73 = !DILocation(line: 124, column: 34, scope: !31)
!74 = !DILocalVariable(name: "msg", arg: 2, scope: !31, file: !1, line: 124, type: !34)
!75 = !DILocation(line: 124, column: 60, scope: !31)
!76 = !DILocalVariable(name: "size", arg: 3, scope: !31, file: !1, line: 124, type: !36)
!77 = !DILocation(line: 124, column: 72, scope: !31)
!78 = !DILocalVariable(name: "index", scope: !31, file: !1, line: 126, type: !4)
!79 = !DILocation(line: 126, column: 11, scope: !31)
!80 = !DILocation(line: 126, column: 29, scope: !31)
!81 = !DILocation(line: 126, column: 34, scope: !31)
!82 = !DILocation(line: 126, column: 19, scope: !31)
!83 = !DILocation(line: 126, column: 41, scope: !31)
!84 = !DILocation(line: 127, column: 17, scope: !31)
!85 = !DILocation(line: 127, column: 2, scope: !31)
!86 = !DILocation(line: 127, column: 7, scope: !31)
!87 = !DILocation(line: 127, column: 14, scope: !31)
!88 = !DILocation(line: 130, column: 6, scope: !89)
!89 = distinct !DILexicalBlock(scope: !31, file: !1, line: 130, column: 6)
!90 = !DILocation(line: 130, column: 6, scope: !31)
!91 = !DILocalVariable(name: "left", scope: !92, file: !1, line: 131, type: !4)
!92 = distinct !DILexicalBlock(scope: !89, file: !1, line: 130, column: 13)
!93 = !DILocation(line: 131, column: 12, scope: !92)
!94 = !DILocation(line: 131, column: 37, scope: !92)
!95 = !DILocation(line: 131, column: 35, scope: !92)
!96 = !DILocation(line: 132, column: 10, scope: !92)
!97 = !DILocation(line: 132, column: 15, scope: !92)
!98 = !DILocation(line: 132, column: 25, scope: !92)
!99 = !DILocation(line: 132, column: 23, scope: !92)
!100 = !DILocation(line: 132, column: 32, scope: !92)
!101 = !DILocation(line: 132, column: 38, scope: !92)
!102 = !DILocation(line: 132, column: 45, scope: !92)
!103 = !DILocation(line: 132, column: 43, scope: !92)
!104 = !DILocation(line: 132, column: 52, scope: !105)
!105 = !DILexicalBlockFile(scope: !92, file: !1, discriminator: 1)
!106 = !DILocation(line: 132, column: 38, scope: !105)
!107 = !DILocation(line: 132, column: 59, scope: !108)
!108 = !DILexicalBlockFile(scope: !92, file: !1, discriminator: 2)
!109 = !DILocation(line: 132, column: 38, scope: !108)
!110 = !DILocation(line: 132, column: 38, scope: !111)
!111 = !DILexicalBlockFile(scope: !92, file: !1, discriminator: 3)
!112 = !DILocation(line: 132, column: 3, scope: !111)
!113 = !DILocation(line: 133, column: 7, scope: !114)
!114 = distinct !DILexicalBlock(scope: !92, file: !1, line: 133, column: 7)
!115 = !DILocation(line: 133, column: 14, scope: !114)
!116 = !DILocation(line: 133, column: 12, scope: !114)
!117 = !DILocation(line: 133, column: 7, scope: !92)
!118 = !DILocation(line: 133, column: 20, scope: !119)
!119 = !DILexicalBlockFile(scope: !114, file: !1, discriminator: 1)
!120 = !DILocation(line: 136, column: 28, scope: !92)
!121 = !DILocation(line: 136, column: 33, scope: !92)
!122 = !DILocation(line: 136, column: 50, scope: !92)
!123 = !DILocation(line: 136, column: 55, scope: !92)
!124 = !DILocation(line: 136, column: 39, scope: !92)
!125 = !DILocation(line: 136, column: 3, scope: !92)
!126 = !DILocation(line: 137, column: 11, scope: !92)
!127 = !DILocation(line: 137, column: 8, scope: !92)
!128 = !DILocation(line: 138, column: 11, scope: !92)
!129 = !DILocation(line: 138, column: 8, scope: !92)
!130 = !DILocation(line: 139, column: 2, scope: !92)
!131 = !DILocation(line: 140, column: 2, scope: !31)
!132 = !DILocation(line: 140, column: 9, scope: !133)
!133 = !DILexicalBlockFile(scope: !31, file: !1, discriminator: 1)
!134 = !DILocation(line: 140, column: 14, scope: !133)
!135 = !DILocation(line: 140, column: 2, scope: !133)
!136 = !DILocalVariable(name: "aligned_message_block", scope: !137, file: !1, line: 141, type: !5)
!137 = distinct !DILexicalBlock(scope: !31, file: !1, line: 140, column: 34)
!138 = !DILocation(line: 141, column: 13, scope: !137)
!139 = !DILocation(line: 142, column: 7, scope: !140)
!140 = distinct !DILexicalBlock(scope: !137, file: !1, line: 142, column: 7)
!141 = !DILocation(line: 142, column: 7, scope: !137)
!142 = !DILocation(line: 145, column: 39, scope: !143)
!143 = distinct !DILexicalBlock(scope: !140, file: !1, line: 142, column: 27)
!144 = !DILocation(line: 145, column: 28, scope: !143)
!145 = !DILocation(line: 145, column: 26, scope: !143)
!146 = !DILocation(line: 146, column: 3, scope: !143)
!147 = !DILocation(line: 147, column: 11, scope: !148)
!148 = distinct !DILexicalBlock(scope: !140, file: !1, line: 146, column: 10)
!149 = !DILocation(line: 147, column: 16, scope: !148)
!150 = !DILocation(line: 147, column: 4, scope: !148)
!151 = !DILocation(line: 147, column: 25, scope: !148)
!152 = !DILocation(line: 148, column: 39, scope: !148)
!153 = !DILocation(line: 148, column: 44, scope: !148)
!154 = !DILocation(line: 148, column: 28, scope: !148)
!155 = !DILocation(line: 148, column: 26, scope: !148)
!156 = !DILocation(line: 151, column: 28, scope: !137)
!157 = !DILocation(line: 151, column: 33, scope: !137)
!158 = !DILocation(line: 151, column: 39, scope: !137)
!159 = !DILocation(line: 151, column: 3, scope: !137)
!160 = !DILocation(line: 152, column: 8, scope: !137)
!161 = !DILocation(line: 153, column: 8, scope: !137)
!162 = !DILocation(line: 140, column: 2, scope: !163)
!163 = !DILexicalBlockFile(scope: !31, file: !1, discriminator: 2)
!164 = !DILocation(line: 155, column: 6, scope: !165)
!165 = distinct !DILexicalBlock(scope: !31, file: !1, line: 155, column: 6)
!166 = !DILocation(line: 155, column: 6, scope: !31)
!167 = !DILocation(line: 157, column: 10, scope: !168)
!168 = distinct !DILexicalBlock(scope: !165, file: !1, line: 155, column: 12)
!169 = !DILocation(line: 157, column: 15, scope: !168)
!170 = !DILocation(line: 157, column: 3, scope: !168)
!171 = !DILocation(line: 157, column: 24, scope: !168)
!172 = !DILocation(line: 157, column: 29, scope: !168)
!173 = !DILocation(line: 158, column: 2, scope: !168)
!174 = !DILocation(line: 159, column: 1, scope: !31)
!175 = !DILocalVariable(name: "hash", arg: 1, scope: !42, file: !1, line: 46, type: !5)
!176 = !DILocation(line: 46, column: 48, scope: !42)
!177 = !DILocalVariable(name: "block", arg: 2, scope: !42, file: !1, line: 46, type: !45)
!178 = !DILocation(line: 46, column: 70, scope: !42)
!179 = !DILocalVariable(name: "t", scope: !42, file: !1, line: 48, type: !180)
!180 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!181 = !DILocation(line: 48, column: 16, scope: !42)
!182 = !DILocalVariable(name: "temp", scope: !42, file: !1, line: 49, type: !183)
!183 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !25, line: 51, baseType: !4)
!184 = !DILocation(line: 49, column: 16, scope: !42)
!185 = !DILocalVariable(name: "W", scope: !42, file: !1, line: 50, type: !186)
!186 = !DICompositeType(tag: DW_TAG_array_type, baseType: !183, size: 2560, align: 32, elements: !187)
!187 = !{!188}
!188 = !DISubrange(count: 80)
!189 = !DILocation(line: 50, column: 16, scope: !42)
!190 = !DILocalVariable(name: "A", scope: !42, file: !1, line: 51, type: !183)
!191 = !DILocation(line: 51, column: 16, scope: !42)
!192 = !DILocalVariable(name: "B", scope: !42, file: !1, line: 51, type: !183)
!193 = !DILocation(line: 51, column: 19, scope: !42)
!194 = !DILocalVariable(name: "C", scope: !42, file: !1, line: 51, type: !183)
!195 = !DILocation(line: 51, column: 22, scope: !42)
!196 = !DILocalVariable(name: "D", scope: !42, file: !1, line: 51, type: !183)
!197 = !DILocation(line: 51, column: 25, scope: !42)
!198 = !DILocalVariable(name: "E", scope: !42, file: !1, line: 51, type: !183)
!199 = !DILocation(line: 51, column: 28, scope: !42)
!200 = !DILocation(line: 54, column: 9, scope: !201)
!201 = distinct !DILexicalBlock(scope: !42, file: !1, line: 54, column: 2)
!202 = !DILocation(line: 54, column: 7, scope: !201)
!203 = !DILocation(line: 54, column: 14, scope: !204)
!204 = !DILexicalBlockFile(scope: !205, file: !1, discriminator: 1)
!205 = distinct !DILexicalBlock(scope: !201, file: !1, line: 54, column: 2)
!206 = !DILocation(line: 54, column: 16, scope: !204)
!207 = !DILocation(line: 54, column: 2, scope: !204)
!208 = !DILocation(line: 56, column: 10, scope: !209)
!209 = distinct !DILexicalBlock(scope: !205, file: !1, line: 54, column: 27)
!210 = !DILocation(line: 56, column: 5, scope: !209)
!211 = !DILocation(line: 56, column: 3, scope: !209)
!212 = !DILocation(line: 56, column: 8, scope: !209)
!213 = !DILocation(line: 57, column: 2, scope: !209)
!214 = !DILocation(line: 54, column: 23, scope: !215)
!215 = !DILexicalBlockFile(scope: !205, file: !1, discriminator: 2)
!216 = !DILocation(line: 54, column: 2, scope: !215)
!217 = !DILocation(line: 60, column: 9, scope: !218)
!218 = distinct !DILexicalBlock(scope: !42, file: !1, line: 60, column: 2)
!219 = !DILocation(line: 60, column: 7, scope: !218)
!220 = !DILocation(line: 60, column: 15, scope: !221)
!221 = !DILexicalBlockFile(scope: !222, file: !1, discriminator: 1)
!222 = distinct !DILexicalBlock(scope: !218, file: !1, line: 60, column: 2)
!223 = !DILocation(line: 60, column: 17, scope: !221)
!224 = !DILocation(line: 60, column: 2, scope: !221)
!225 = !DILocation(line: 61, column: 10, scope: !226)
!226 = distinct !DILexicalBlock(scope: !222, file: !1, line: 60, column: 28)
!227 = !DILocation(line: 61, column: 5, scope: !226)
!228 = !DILocation(line: 61, column: 3, scope: !226)
!229 = !DILocation(line: 61, column: 8, scope: !226)
!230 = !DILocation(line: 62, column: 2, scope: !226)
!231 = !DILocation(line: 60, column: 24, scope: !232)
!232 = !DILexicalBlockFile(scope: !222, file: !1, discriminator: 2)
!233 = !DILocation(line: 60, column: 2, scope: !232)
!234 = !DILocation(line: 64, column: 6, scope: !42)
!235 = !DILocation(line: 64, column: 4, scope: !42)
!236 = !DILocation(line: 65, column: 6, scope: !42)
!237 = !DILocation(line: 65, column: 4, scope: !42)
!238 = !DILocation(line: 66, column: 6, scope: !42)
!239 = !DILocation(line: 66, column: 4, scope: !42)
!240 = !DILocation(line: 67, column: 6, scope: !42)
!241 = !DILocation(line: 67, column: 4, scope: !42)
!242 = !DILocation(line: 68, column: 6, scope: !42)
!243 = !DILocation(line: 68, column: 4, scope: !42)
!244 = !DILocation(line: 70, column: 9, scope: !245)
!245 = distinct !DILexicalBlock(scope: !42, file: !1, line: 70, column: 2)
!246 = !DILocation(line: 70, column: 7, scope: !245)
!247 = !DILocation(line: 70, column: 14, scope: !248)
!248 = !DILexicalBlockFile(scope: !249, file: !1, discriminator: 1)
!249 = distinct !DILexicalBlock(scope: !245, file: !1, line: 70, column: 2)
!250 = !DILocation(line: 70, column: 16, scope: !248)
!251 = !DILocation(line: 70, column: 2, scope: !248)
!252 = !DILocation(line: 72, column: 11, scope: !253)
!253 = distinct !DILexicalBlock(scope: !249, file: !1, line: 70, column: 27)
!254 = !DILocation(line: 72, column: 29, scope: !253)
!255 = !DILocation(line: 72, column: 33, scope: !253)
!256 = !DILocation(line: 72, column: 31, scope: !253)
!257 = !DILocation(line: 72, column: 38, scope: !253)
!258 = !DILocation(line: 72, column: 36, scope: !253)
!259 = !DILocation(line: 72, column: 43, scope: !253)
!260 = !DILocation(line: 72, column: 41, scope: !253)
!261 = !DILocation(line: 72, column: 24, scope: !253)
!262 = !DILocation(line: 73, column: 6, scope: !253)
!263 = !DILocation(line: 73, column: 4, scope: !253)
!264 = !DILocation(line: 73, column: 12, scope: !253)
!265 = !DILocation(line: 73, column: 10, scope: !253)
!266 = !DILocation(line: 73, column: 8, scope: !253)
!267 = !DILocation(line: 73, column: 15, scope: !253)
!268 = !DILocation(line: 72, column: 8, scope: !253)
!269 = !DILocation(line: 74, column: 7, scope: !253)
!270 = !DILocation(line: 74, column: 5, scope: !253)
!271 = !DILocation(line: 75, column: 7, scope: !253)
!272 = !DILocation(line: 75, column: 5, scope: !253)
!273 = !DILocation(line: 76, column: 7, scope: !253)
!274 = !DILocation(line: 76, column: 5, scope: !253)
!275 = !DILocation(line: 77, column: 7, scope: !253)
!276 = !DILocation(line: 77, column: 5, scope: !253)
!277 = !DILocation(line: 78, column: 7, scope: !253)
!278 = !DILocation(line: 78, column: 5, scope: !253)
!279 = !DILocation(line: 79, column: 2, scope: !253)
!280 = !DILocation(line: 70, column: 23, scope: !281)
!281 = !DILexicalBlockFile(scope: !249, file: !1, discriminator: 2)
!282 = !DILocation(line: 70, column: 2, scope: !281)
!283 = !DILocation(line: 81, column: 9, scope: !284)
!284 = distinct !DILexicalBlock(scope: !42, file: !1, line: 81, column: 2)
!285 = !DILocation(line: 81, column: 7, scope: !284)
!286 = !DILocation(line: 81, column: 15, scope: !287)
!287 = !DILexicalBlockFile(scope: !288, file: !1, discriminator: 1)
!288 = distinct !DILexicalBlock(scope: !284, file: !1, line: 81, column: 2)
!289 = !DILocation(line: 81, column: 17, scope: !287)
!290 = !DILocation(line: 81, column: 2, scope: !287)
!291 = !DILocation(line: 82, column: 10, scope: !292)
!292 = distinct !DILexicalBlock(scope: !288, file: !1, line: 81, column: 28)
!293 = !DILocation(line: 82, column: 26, scope: !292)
!294 = !DILocation(line: 82, column: 30, scope: !292)
!295 = !DILocation(line: 82, column: 28, scope: !292)
!296 = !DILocation(line: 82, column: 34, scope: !292)
!297 = !DILocation(line: 82, column: 32, scope: !292)
!298 = !DILocation(line: 82, column: 23, scope: !292)
!299 = !DILocation(line: 82, column: 39, scope: !292)
!300 = !DILocation(line: 82, column: 37, scope: !292)
!301 = !DILocation(line: 82, column: 45, scope: !292)
!302 = !DILocation(line: 82, column: 43, scope: !292)
!303 = !DILocation(line: 82, column: 41, scope: !292)
!304 = !DILocation(line: 82, column: 48, scope: !292)
!305 = !DILocation(line: 82, column: 8, scope: !292)
!306 = !DILocation(line: 83, column: 7, scope: !292)
!307 = !DILocation(line: 83, column: 5, scope: !292)
!308 = !DILocation(line: 84, column: 7, scope: !292)
!309 = !DILocation(line: 84, column: 5, scope: !292)
!310 = !DILocation(line: 85, column: 7, scope: !292)
!311 = !DILocation(line: 85, column: 5, scope: !292)
!312 = !DILocation(line: 86, column: 7, scope: !292)
!313 = !DILocation(line: 86, column: 5, scope: !292)
!314 = !DILocation(line: 87, column: 7, scope: !292)
!315 = !DILocation(line: 87, column: 5, scope: !292)
!316 = !DILocation(line: 88, column: 2, scope: !292)
!317 = !DILocation(line: 81, column: 24, scope: !318)
!318 = !DILexicalBlockFile(scope: !288, file: !1, discriminator: 2)
!319 = !DILocation(line: 81, column: 2, scope: !318)
!320 = !DILocation(line: 90, column: 9, scope: !321)
!321 = distinct !DILexicalBlock(scope: !42, file: !1, line: 90, column: 2)
!322 = !DILocation(line: 90, column: 7, scope: !321)
!323 = !DILocation(line: 90, column: 15, scope: !324)
!324 = !DILexicalBlockFile(scope: !325, file: !1, discriminator: 1)
!325 = distinct !DILexicalBlock(scope: !321, file: !1, line: 90, column: 2)
!326 = !DILocation(line: 90, column: 17, scope: !324)
!327 = !DILocation(line: 90, column: 2, scope: !324)
!328 = !DILocation(line: 91, column: 10, scope: !329)
!329 = distinct !DILexicalBlock(scope: !325, file: !1, line: 90, column: 28)
!330 = !DILocation(line: 91, column: 27, scope: !329)
!331 = !DILocation(line: 91, column: 31, scope: !329)
!332 = !DILocation(line: 91, column: 29, scope: !329)
!333 = !DILocation(line: 91, column: 37, scope: !329)
!334 = !DILocation(line: 91, column: 41, scope: !329)
!335 = !DILocation(line: 91, column: 39, scope: !329)
!336 = !DILocation(line: 91, column: 34, scope: !329)
!337 = !DILocation(line: 91, column: 47, scope: !329)
!338 = !DILocation(line: 91, column: 51, scope: !329)
!339 = !DILocation(line: 91, column: 49, scope: !329)
!340 = !DILocation(line: 91, column: 44, scope: !329)
!341 = !DILocation(line: 91, column: 23, scope: !329)
!342 = !DILocation(line: 92, column: 6, scope: !329)
!343 = !DILocation(line: 92, column: 4, scope: !329)
!344 = !DILocation(line: 92, column: 12, scope: !329)
!345 = !DILocation(line: 92, column: 10, scope: !329)
!346 = !DILocation(line: 92, column: 8, scope: !329)
!347 = !DILocation(line: 92, column: 15, scope: !329)
!348 = !DILocation(line: 91, column: 8, scope: !329)
!349 = !DILocation(line: 93, column: 7, scope: !329)
!350 = !DILocation(line: 93, column: 5, scope: !329)
!351 = !DILocation(line: 94, column: 7, scope: !329)
!352 = !DILocation(line: 94, column: 5, scope: !329)
!353 = !DILocation(line: 95, column: 7, scope: !329)
!354 = !DILocation(line: 95, column: 5, scope: !329)
!355 = !DILocation(line: 96, column: 7, scope: !329)
!356 = !DILocation(line: 96, column: 5, scope: !329)
!357 = !DILocation(line: 97, column: 7, scope: !329)
!358 = !DILocation(line: 97, column: 5, scope: !329)
!359 = !DILocation(line: 98, column: 2, scope: !329)
!360 = !DILocation(line: 90, column: 24, scope: !361)
!361 = !DILexicalBlockFile(scope: !325, file: !1, discriminator: 2)
!362 = !DILocation(line: 90, column: 2, scope: !361)
!363 = !DILocation(line: 100, column: 9, scope: !364)
!364 = distinct !DILexicalBlock(scope: !42, file: !1, line: 100, column: 2)
!365 = !DILocation(line: 100, column: 7, scope: !364)
!366 = !DILocation(line: 100, column: 15, scope: !367)
!367 = !DILexicalBlockFile(scope: !368, file: !1, discriminator: 1)
!368 = distinct !DILexicalBlock(scope: !364, file: !1, line: 100, column: 2)
!369 = !DILocation(line: 100, column: 17, scope: !367)
!370 = !DILocation(line: 100, column: 2, scope: !367)
!371 = !DILocation(line: 101, column: 10, scope: !372)
!372 = distinct !DILexicalBlock(scope: !368, file: !1, line: 100, column: 28)
!373 = !DILocation(line: 101, column: 26, scope: !372)
!374 = !DILocation(line: 101, column: 30, scope: !372)
!375 = !DILocation(line: 101, column: 28, scope: !372)
!376 = !DILocation(line: 101, column: 34, scope: !372)
!377 = !DILocation(line: 101, column: 32, scope: !372)
!378 = !DILocation(line: 101, column: 23, scope: !372)
!379 = !DILocation(line: 101, column: 39, scope: !372)
!380 = !DILocation(line: 101, column: 37, scope: !372)
!381 = !DILocation(line: 101, column: 45, scope: !372)
!382 = !DILocation(line: 101, column: 43, scope: !372)
!383 = !DILocation(line: 101, column: 41, scope: !372)
!384 = !DILocation(line: 101, column: 48, scope: !372)
!385 = !DILocation(line: 101, column: 8, scope: !372)
!386 = !DILocation(line: 102, column: 7, scope: !372)
!387 = !DILocation(line: 102, column: 5, scope: !372)
!388 = !DILocation(line: 103, column: 7, scope: !372)
!389 = !DILocation(line: 103, column: 5, scope: !372)
!390 = !DILocation(line: 104, column: 7, scope: !372)
!391 = !DILocation(line: 104, column: 5, scope: !372)
!392 = !DILocation(line: 105, column: 7, scope: !372)
!393 = !DILocation(line: 105, column: 5, scope: !372)
!394 = !DILocation(line: 106, column: 7, scope: !372)
!395 = !DILocation(line: 106, column: 5, scope: !372)
!396 = !DILocation(line: 107, column: 2, scope: !372)
!397 = !DILocation(line: 100, column: 24, scope: !398)
!398 = !DILexicalBlockFile(scope: !368, file: !1, discriminator: 2)
!399 = !DILocation(line: 100, column: 2, scope: !398)
!400 = !DILocation(line: 109, column: 13, scope: !42)
!401 = !DILocation(line: 109, column: 2, scope: !42)
!402 = !DILocation(line: 109, column: 10, scope: !42)
!403 = !DILocation(line: 110, column: 13, scope: !42)
!404 = !DILocation(line: 110, column: 2, scope: !42)
!405 = !DILocation(line: 110, column: 10, scope: !42)
!406 = !DILocation(line: 111, column: 13, scope: !42)
!407 = !DILocation(line: 111, column: 2, scope: !42)
!408 = !DILocation(line: 111, column: 10, scope: !42)
!409 = !DILocation(line: 112, column: 13, scope: !42)
!410 = !DILocation(line: 112, column: 2, scope: !42)
!411 = !DILocation(line: 112, column: 10, scope: !42)
!412 = !DILocation(line: 113, column: 13, scope: !42)
!413 = !DILocation(line: 113, column: 2, scope: !42)
!414 = !DILocation(line: 113, column: 10, scope: !42)
!415 = !DILocation(line: 114, column: 1, scope: !42)
!416 = !DILocalVariable(name: "ctx", arg: 1, scope: !38, file: !1, line: 167, type: !13)
!417 = !DILocation(line: 167, column: 33, scope: !38)
!418 = !DILocalVariable(name: "result", arg: 2, scope: !38, file: !1, line: 167, type: !41)
!419 = !DILocation(line: 167, column: 53, scope: !38)
!420 = !DILocalVariable(name: "index", scope: !38, file: !1, line: 169, type: !4)
!421 = !DILocation(line: 169, column: 12, scope: !38)
!422 = !DILocation(line: 169, column: 30, scope: !38)
!423 = !DILocation(line: 169, column: 35, scope: !38)
!424 = !DILocation(line: 169, column: 20, scope: !38)
!425 = !DILocation(line: 169, column: 42, scope: !38)
!426 = !DILocalVariable(name: "msg32", scope: !38, file: !1, line: 170, type: !5)
!427 = !DILocation(line: 170, column: 12, scope: !38)
!428 = !DILocation(line: 170, column: 31, scope: !38)
!429 = !DILocation(line: 170, column: 36, scope: !38)
!430 = !DILocation(line: 170, column: 20, scope: !38)
!431 = !DILocation(line: 173, column: 20, scope: !38)
!432 = !DILocation(line: 173, column: 2, scope: !38)
!433 = !DILocation(line: 173, column: 7, scope: !38)
!434 = !DILocation(line: 173, column: 24, scope: !38)
!435 = !DILocation(line: 174, column: 2, scope: !38)
!436 = !DILocation(line: 174, column: 10, scope: !437)
!437 = !DILexicalBlockFile(scope: !38, file: !1, discriminator: 1)
!438 = !DILocation(line: 174, column: 16, scope: !437)
!439 = !DILocation(line: 174, column: 21, scope: !437)
!440 = !DILocation(line: 174, column: 2, scope: !437)
!441 = !DILocation(line: 175, column: 21, scope: !442)
!442 = distinct !DILexicalBlock(scope: !38, file: !1, line: 174, column: 27)
!443 = !DILocation(line: 175, column: 3, scope: !442)
!444 = !DILocation(line: 175, column: 8, scope: !442)
!445 = !DILocation(line: 175, column: 25, scope: !442)
!446 = !DILocation(line: 174, column: 2, scope: !447)
!447 = !DILexicalBlockFile(scope: !38, file: !1, discriminator: 2)
!448 = !DILocation(line: 177, column: 8, scope: !38)
!449 = !DILocation(line: 180, column: 6, scope: !450)
!450 = distinct !DILexicalBlock(scope: !38, file: !1, line: 180, column: 6)
!451 = !DILocation(line: 180, column: 12, scope: !450)
!452 = !DILocation(line: 180, column: 6, scope: !38)
!453 = !DILocation(line: 182, column: 3, scope: !454)
!454 = distinct !DILexicalBlock(scope: !450, file: !1, line: 180, column: 18)
!455 = !DILocation(line: 182, column: 10, scope: !456)
!456 = !DILexicalBlockFile(scope: !454, file: !1, discriminator: 1)
!457 = !DILocation(line: 182, column: 16, scope: !456)
!458 = !DILocation(line: 182, column: 3, scope: !456)
!459 = !DILocation(line: 183, column: 15, scope: !460)
!460 = distinct !DILexicalBlock(scope: !454, file: !1, line: 182, column: 22)
!461 = !DILocation(line: 183, column: 4, scope: !460)
!462 = !DILocation(line: 183, column: 19, scope: !460)
!463 = !DILocation(line: 182, column: 3, scope: !464)
!464 = !DILexicalBlockFile(scope: !454, file: !1, discriminator: 2)
!465 = !DILocation(line: 185, column: 28, scope: !454)
!466 = !DILocation(line: 185, column: 33, scope: !454)
!467 = !DILocation(line: 185, column: 39, scope: !454)
!468 = !DILocation(line: 185, column: 3, scope: !454)
!469 = !DILocation(line: 186, column: 9, scope: !454)
!470 = !DILocation(line: 187, column: 2, scope: !454)
!471 = !DILocation(line: 188, column: 2, scope: !38)
!472 = !DILocation(line: 188, column: 9, scope: !437)
!473 = !DILocation(line: 188, column: 15, scope: !437)
!474 = !DILocation(line: 188, column: 2, scope: !437)
!475 = !DILocation(line: 189, column: 14, scope: !476)
!476 = distinct !DILexicalBlock(scope: !38, file: !1, line: 188, column: 21)
!477 = !DILocation(line: 189, column: 3, scope: !476)
!478 = !DILocation(line: 189, column: 18, scope: !476)
!479 = !DILocation(line: 188, column: 2, scope: !447)
!480 = !DILocation(line: 191, column: 14, scope: !38)
!481 = !DILocation(line: 191, column: 2, scope: !38)
!482 = !DILocation(line: 191, column: 12, scope: !38)
!483 = !DILocation(line: 192, column: 14, scope: !38)
!484 = !DILocation(line: 192, column: 2, scope: !38)
!485 = !DILocation(line: 192, column: 12, scope: !38)
!486 = !DILocation(line: 193, column: 27, scope: !38)
!487 = !DILocation(line: 193, column: 32, scope: !38)
!488 = !DILocation(line: 193, column: 38, scope: !38)
!489 = !DILocation(line: 193, column: 2, scope: !38)
!490 = !DILocation(line: 195, column: 6, scope: !491)
!491 = distinct !DILexicalBlock(scope: !38, file: !1, line: 195, column: 6)
!492 = !DILocation(line: 195, column: 6, scope: !38)
!493 = !DILocation(line: 195, column: 14, scope: !494)
!494 = !DILexicalBlockFile(scope: !491, file: !1, discriminator: 1)
!495 = !DILocation(line: 196, column: 1, scope: !38)
