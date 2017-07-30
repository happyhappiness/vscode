; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/sha3.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.sha3_ctx = type { [25 x i64], [24 x i64], i32, i32 }

@.str = private unnamed_addr constant [27 x i8] c"block_size > digest_length\00", align 1
@.str.1 = private unnamed_addr constant [71 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/sha3.c\00", align 1
@__PRETTY_FUNCTION__.rhash_sha3_final = private unnamed_addr constant [51 x i8] c"void rhash_sha3_final(sha3_ctx *, unsigned char *)\00", align 1
@.str.2 = private unnamed_addr constant [33 x i8] c"rate <= 1600 && (rate % 64) == 0\00", align 1
@__PRETTY_FUNCTION__.rhash_keccak_init = private unnamed_addr constant [49 x i8] c"void rhash_keccak_init(sha3_ctx *, unsigned int)\00", align 1
@keccak_round_constants = internal global [24 x i64] [i64 1, i64 32898, i64 -9223372036854742902, i64 -9223372034707259392, i64 32907, i64 2147483649, i64 -9223372034707259263, i64 -9223372036854743031, i64 138, i64 136, i64 2147516425, i64 2147483658, i64 2147516555, i64 -9223372036854775669, i64 -9223372036854742903, i64 -9223372036854743037, i64 -9223372036854743038, i64 -9223372036854775680, i64 32778, i64 -9223372034707292150, i64 -9223372034707259263, i64 -9223372036854742912, i64 2147483649, i64 -9223372034707259384], align 16

; Function Attrs: nounwind uwtable
define void @rhash_sha3_224_init(%struct.sha3_ctx* %ctx) #0 !dbg !16 {
entry:
  %ctx.addr = alloca %struct.sha3_ctx*, align 8
  store %struct.sha3_ctx* %ctx, %struct.sha3_ctx** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sha3_ctx** %ctx.addr, metadata !66, metadata !67), !dbg !68
  %0 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !69
  call void @rhash_keccak_init(%struct.sha3_ctx* %0, i32 224), !dbg !70
  ret void, !dbg !71
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal void @rhash_keccak_init(%struct.sha3_ctx* %ctx, i32 %bits) #0 !dbg !47 {
entry:
  %ctx.addr = alloca %struct.sha3_ctx*, align 8
  %bits.addr = alloca i32, align 4
  %rate = alloca i32, align 4
  store %struct.sha3_ctx* %ctx, %struct.sha3_ctx** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sha3_ctx** %ctx.addr, metadata !72, metadata !67), !dbg !73
  store i32 %bits, i32* %bits.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %bits.addr, metadata !74, metadata !67), !dbg !75
  call void @llvm.dbg.declare(metadata i32* %rate, metadata !76, metadata !67), !dbg !77
  %0 = load i32, i32* %bits.addr, align 4, !dbg !78
  %mul = mul i32 %0, 2, !dbg !79
  %sub = sub i32 1600, %mul, !dbg !80
  store i32 %sub, i32* %rate, align 4, !dbg !77
  %1 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !81
  %2 = bitcast %struct.sha3_ctx* %1 to i8*, !dbg !82
  call void @llvm.memset.p0i8.i64(i8* %2, i8 0, i64 400, i32 8, i1 false), !dbg !82
  %3 = load i32, i32* %rate, align 4, !dbg !83
  %div = udiv i32 %3, 8, !dbg !84
  %4 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !85
  %block_size = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %4, i32 0, i32 3, !dbg !86
  store i32 %div, i32* %block_size, align 4, !dbg !87
  %5 = load i32, i32* %rate, align 4, !dbg !88
  %cmp = icmp ule i32 %5, 1600, !dbg !88
  br i1 %cmp, label %land.lhs.true, label %cond.false, !dbg !88

land.lhs.true:                                    ; preds = %entry
  %6 = load i32, i32* %rate, align 4, !dbg !89
  %rem = urem i32 %6, 64, !dbg !89
  %cmp1 = icmp eq i32 %rem, 0, !dbg !89
  br i1 %cmp1, label %cond.true, label %cond.false, !dbg !89

cond.true:                                        ; preds = %land.lhs.true
  br label %cond.end, !dbg !91

cond.false:                                       ; preds = %land.lhs.true, %entry
  call void @__assert_fail(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.1, i32 0, i32 0), i32 46, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @__PRETTY_FUNCTION__.rhash_keccak_init, i32 0, i32 0)) #4, !dbg !93
  unreachable, !dbg !93
                                                  ; No predecessors!
  br label %cond.end, !dbg !95

cond.end:                                         ; preds = %7, %cond.true
  ret void, !dbg !97
}

; Function Attrs: nounwind uwtable
define void @rhash_sha3_256_init(%struct.sha3_ctx* %ctx) #0 !dbg !34 {
entry:
  %ctx.addr = alloca %struct.sha3_ctx*, align 8
  store %struct.sha3_ctx* %ctx, %struct.sha3_ctx** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sha3_ctx** %ctx.addr, metadata !98, metadata !67), !dbg !99
  %0 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !100
  call void @rhash_keccak_init(%struct.sha3_ctx* %0, i32 256), !dbg !101
  ret void, !dbg !102
}

; Function Attrs: nounwind uwtable
define void @rhash_sha3_384_init(%struct.sha3_ctx* %ctx) #0 !dbg !35 {
entry:
  %ctx.addr = alloca %struct.sha3_ctx*, align 8
  store %struct.sha3_ctx* %ctx, %struct.sha3_ctx** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sha3_ctx** %ctx.addr, metadata !103, metadata !67), !dbg !104
  %0 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !105
  call void @rhash_keccak_init(%struct.sha3_ctx* %0, i32 384), !dbg !106
  ret void, !dbg !107
}

; Function Attrs: nounwind uwtable
define void @rhash_sha3_512_init(%struct.sha3_ctx* %ctx) #0 !dbg !36 {
entry:
  %ctx.addr = alloca %struct.sha3_ctx*, align 8
  store %struct.sha3_ctx* %ctx, %struct.sha3_ctx** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sha3_ctx** %ctx.addr, metadata !108, metadata !67), !dbg !109
  %0 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !110
  call void @rhash_keccak_init(%struct.sha3_ctx* %0, i32 512), !dbg !111
  ret void, !dbg !112
}

; Function Attrs: nounwind uwtable
define void @rhash_sha3_update(%struct.sha3_ctx* %ctx, i8* %msg, i64 %size) #0 !dbg !37 {
entry:
  %ctx.addr = alloca %struct.sha3_ctx*, align 8
  %msg.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %index = alloca i64, align 8
  %block_size = alloca i64, align 8
  %left = alloca i64, align 8
  %aligned_message_block = alloca i64*, align 8
  store %struct.sha3_ctx* %ctx, %struct.sha3_ctx** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sha3_ctx** %ctx.addr, metadata !113, metadata !67), !dbg !114
  store i8* %msg, i8** %msg.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %msg.addr, metadata !115, metadata !67), !dbg !116
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !117, metadata !67), !dbg !118
  call void @llvm.dbg.declare(metadata i64* %index, metadata !119, metadata !67), !dbg !120
  %0 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !121
  %rest = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %0, i32 0, i32 2, !dbg !122
  %1 = load i32, i32* %rest, align 8, !dbg !122
  %conv = zext i32 %1 to i64, !dbg !123
  store i64 %conv, i64* %index, align 8, !dbg !120
  call void @llvm.dbg.declare(metadata i64* %block_size, metadata !124, metadata !67), !dbg !125
  %2 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !126
  %block_size1 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %2, i32 0, i32 3, !dbg !127
  %3 = load i32, i32* %block_size1, align 4, !dbg !127
  %conv2 = zext i32 %3 to i64, !dbg !128
  store i64 %conv2, i64* %block_size, align 8, !dbg !125
  %4 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !129
  %rest3 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %4, i32 0, i32 2, !dbg !131
  %5 = load i32, i32* %rest3, align 8, !dbg !131
  %and = and i32 %5, -2147483648, !dbg !132
  %tobool = icmp ne i32 %and, 0, !dbg !132
  br i1 %tobool, label %if.then, label %if.end, !dbg !133

if.then:                                          ; preds = %entry
  br label %if.end40, !dbg !134

if.end:                                           ; preds = %entry
  %6 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !136
  %rest4 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %6, i32 0, i32 2, !dbg !137
  %7 = load i32, i32* %rest4, align 8, !dbg !137
  %conv5 = zext i32 %7 to i64, !dbg !136
  %8 = load i64, i64* %size.addr, align 8, !dbg !138
  %add = add i64 %conv5, %8, !dbg !139
  %9 = load i64, i64* %block_size, align 8, !dbg !140
  %rem = urem i64 %add, %9, !dbg !141
  %conv6 = trunc i64 %rem to i32, !dbg !142
  %10 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !143
  %rest7 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %10, i32 0, i32 2, !dbg !144
  store i32 %conv6, i32* %rest7, align 8, !dbg !145
  %11 = load i64, i64* %index, align 8, !dbg !146
  %tobool8 = icmp ne i64 %11, 0, !dbg !146
  br i1 %tobool8, label %if.then9, label %if.end20, !dbg !148

if.then9:                                         ; preds = %if.end
  call void @llvm.dbg.declare(metadata i64* %left, metadata !149, metadata !67), !dbg !151
  %12 = load i64, i64* %block_size, align 8, !dbg !152
  %13 = load i64, i64* %index, align 8, !dbg !153
  %sub = sub i64 %12, %13, !dbg !154
  store i64 %sub, i64* %left, align 8, !dbg !151
  %14 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !155
  %message = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %14, i32 0, i32 1, !dbg !156
  %arraydecay = getelementptr inbounds [24 x i64], [24 x i64]* %message, i32 0, i32 0, !dbg !155
  %15 = bitcast i64* %arraydecay to i8*, !dbg !157
  %16 = load i64, i64* %index, align 8, !dbg !158
  %add.ptr = getelementptr inbounds i8, i8* %15, i64 %16, !dbg !159
  %17 = load i8*, i8** %msg.addr, align 8, !dbg !160
  %18 = load i64, i64* %size.addr, align 8, !dbg !161
  %19 = load i64, i64* %left, align 8, !dbg !162
  %cmp = icmp ult i64 %18, %19, !dbg !163
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !161

cond.true:                                        ; preds = %if.then9
  %20 = load i64, i64* %size.addr, align 8, !dbg !164
  br label %cond.end, !dbg !166

cond.false:                                       ; preds = %if.then9
  %21 = load i64, i64* %left, align 8, !dbg !167
  br label %cond.end, !dbg !169

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %20, %cond.true ], [ %21, %cond.false ], !dbg !170
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %17, i64 %cond, i32 1, i1 false), !dbg !172
  %22 = load i64, i64* %size.addr, align 8, !dbg !173
  %23 = load i64, i64* %left, align 8, !dbg !175
  %cmp11 = icmp ult i64 %22, %23, !dbg !176
  br i1 %cmp11, label %if.then13, label %if.end14, !dbg !177

if.then13:                                        ; preds = %cond.end
  br label %if.end40, !dbg !178

if.end14:                                         ; preds = %cond.end
  %24 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !180
  %hash = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %24, i32 0, i32 0, !dbg !181
  %arraydecay15 = getelementptr inbounds [25 x i64], [25 x i64]* %hash, i32 0, i32 0, !dbg !180
  %25 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !182
  %message16 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %25, i32 0, i32 1, !dbg !183
  %arraydecay17 = getelementptr inbounds [24 x i64], [24 x i64]* %message16, i32 0, i32 0, !dbg !182
  %26 = load i64, i64* %block_size, align 8, !dbg !184
  call void @rhash_sha3_process_block(i64* %arraydecay15, i64* %arraydecay17, i64 %26), !dbg !185
  %27 = load i64, i64* %left, align 8, !dbg !186
  %28 = load i8*, i8** %msg.addr, align 8, !dbg !187
  %add.ptr18 = getelementptr inbounds i8, i8* %28, i64 %27, !dbg !187
  store i8* %add.ptr18, i8** %msg.addr, align 8, !dbg !187
  %29 = load i64, i64* %left, align 8, !dbg !188
  %30 = load i64, i64* %size.addr, align 8, !dbg !189
  %sub19 = sub i64 %30, %29, !dbg !189
  store i64 %sub19, i64* %size.addr, align 8, !dbg !189
  br label %if.end20, !dbg !190

if.end20:                                         ; preds = %if.end14, %if.end
  br label %while.cond, !dbg !191

while.cond:                                       ; preds = %if.end31, %if.end20
  %31 = load i64, i64* %size.addr, align 8, !dbg !192
  %32 = load i64, i64* %block_size, align 8, !dbg !194
  %cmp21 = icmp uge i64 %31, %32, !dbg !195
  br i1 %cmp21, label %while.body, label %while.end, !dbg !196

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i64** %aligned_message_block, metadata !197, metadata !67), !dbg !199
  %33 = load i8*, i8** %msg.addr, align 8, !dbg !200
  %sub.ptr.lhs.cast = ptrtoint i8* %33 to i64, !dbg !200
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, 0, !dbg !200
  %and23 = and i64 7, %sub.ptr.sub, !dbg !200
  %cmp24 = icmp eq i64 0, %and23, !dbg !200
  br i1 %cmp24, label %if.then26, label %if.else, !dbg !202

if.then26:                                        ; preds = %while.body
  %34 = load i8*, i8** %msg.addr, align 8, !dbg !203
  %35 = bitcast i8* %34 to i64*, !dbg !205
  store i64* %35, i64** %aligned_message_block, align 8, !dbg !206
  br label %if.end31, !dbg !207

if.else:                                          ; preds = %while.body
  %36 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !208
  %message27 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %36, i32 0, i32 1, !dbg !210
  %arraydecay28 = getelementptr inbounds [24 x i64], [24 x i64]* %message27, i32 0, i32 0, !dbg !211
  %37 = bitcast i64* %arraydecay28 to i8*, !dbg !211
  %38 = load i8*, i8** %msg.addr, align 8, !dbg !212
  %39 = load i64, i64* %block_size, align 8, !dbg !213
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %37, i8* %38, i64 %39, i32 1, i1 false), !dbg !211
  %40 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !214
  %message29 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %40, i32 0, i32 1, !dbg !215
  %arraydecay30 = getelementptr inbounds [24 x i64], [24 x i64]* %message29, i32 0, i32 0, !dbg !214
  store i64* %arraydecay30, i64** %aligned_message_block, align 8, !dbg !216
  br label %if.end31

if.end31:                                         ; preds = %if.else, %if.then26
  %41 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !217
  %hash32 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %41, i32 0, i32 0, !dbg !218
  %arraydecay33 = getelementptr inbounds [25 x i64], [25 x i64]* %hash32, i32 0, i32 0, !dbg !217
  %42 = load i64*, i64** %aligned_message_block, align 8, !dbg !219
  %43 = load i64, i64* %block_size, align 8, !dbg !220
  call void @rhash_sha3_process_block(i64* %arraydecay33, i64* %42, i64 %43), !dbg !221
  %44 = load i64, i64* %block_size, align 8, !dbg !222
  %45 = load i8*, i8** %msg.addr, align 8, !dbg !223
  %add.ptr34 = getelementptr inbounds i8, i8* %45, i64 %44, !dbg !223
  store i8* %add.ptr34, i8** %msg.addr, align 8, !dbg !223
  %46 = load i64, i64* %block_size, align 8, !dbg !224
  %47 = load i64, i64* %size.addr, align 8, !dbg !225
  %sub35 = sub i64 %47, %46, !dbg !225
  store i64 %sub35, i64* %size.addr, align 8, !dbg !225
  br label %while.cond, !dbg !226

while.end:                                        ; preds = %while.cond
  %48 = load i64, i64* %size.addr, align 8, !dbg !228
  %tobool36 = icmp ne i64 %48, 0, !dbg !228
  br i1 %tobool36, label %if.then37, label %if.end40, !dbg !230

if.then37:                                        ; preds = %while.end
  %49 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !231
  %message38 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %49, i32 0, i32 1, !dbg !233
  %arraydecay39 = getelementptr inbounds [24 x i64], [24 x i64]* %message38, i32 0, i32 0, !dbg !234
  %50 = bitcast i64* %arraydecay39 to i8*, !dbg !234
  %51 = load i8*, i8** %msg.addr, align 8, !dbg !235
  %52 = load i64, i64* %size.addr, align 8, !dbg !236
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %50, i8* %51, i64 %52, i32 1, i1 false), !dbg !234
  br label %if.end40, !dbg !237

if.end40:                                         ; preds = %if.then, %if.then13, %if.then37, %while.end
  ret void, !dbg !238
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

; Function Attrs: nounwind uwtable
define internal void @rhash_sha3_process_block(i64* %hash, i64* %block, i64 %block_size) #0 !dbg !50 {
entry:
  %hash.addr = alloca i64*, align 8
  %block.addr = alloca i64*, align 8
  %block_size.addr = alloca i64, align 8
  store i64* %hash, i64** %hash.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %hash.addr, metadata !239, metadata !67), !dbg !240
  store i64* %block, i64** %block.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %block.addr, metadata !241, metadata !67), !dbg !242
  store i64 %block_size, i64* %block_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %block_size.addr, metadata !243, metadata !67), !dbg !244
  %0 = load i64*, i64** %block.addr, align 8, !dbg !245
  %arrayidx = getelementptr inbounds i64, i64* %0, i64 0, !dbg !245
  %1 = load i64, i64* %arrayidx, align 8, !dbg !245
  %2 = load i64*, i64** %hash.addr, align 8, !dbg !246
  %arrayidx1 = getelementptr inbounds i64, i64* %2, i64 0, !dbg !246
  %3 = load i64, i64* %arrayidx1, align 8, !dbg !247
  %xor = xor i64 %3, %1, !dbg !247
  store i64 %xor, i64* %arrayidx1, align 8, !dbg !247
  %4 = load i64*, i64** %block.addr, align 8, !dbg !248
  %arrayidx2 = getelementptr inbounds i64, i64* %4, i64 1, !dbg !248
  %5 = load i64, i64* %arrayidx2, align 8, !dbg !248
  %6 = load i64*, i64** %hash.addr, align 8, !dbg !249
  %arrayidx3 = getelementptr inbounds i64, i64* %6, i64 1, !dbg !249
  %7 = load i64, i64* %arrayidx3, align 8, !dbg !250
  %xor4 = xor i64 %7, %5, !dbg !250
  store i64 %xor4, i64* %arrayidx3, align 8, !dbg !250
  %8 = load i64*, i64** %block.addr, align 8, !dbg !251
  %arrayidx5 = getelementptr inbounds i64, i64* %8, i64 2, !dbg !251
  %9 = load i64, i64* %arrayidx5, align 8, !dbg !251
  %10 = load i64*, i64** %hash.addr, align 8, !dbg !252
  %arrayidx6 = getelementptr inbounds i64, i64* %10, i64 2, !dbg !252
  %11 = load i64, i64* %arrayidx6, align 8, !dbg !253
  %xor7 = xor i64 %11, %9, !dbg !253
  store i64 %xor7, i64* %arrayidx6, align 8, !dbg !253
  %12 = load i64*, i64** %block.addr, align 8, !dbg !254
  %arrayidx8 = getelementptr inbounds i64, i64* %12, i64 3, !dbg !254
  %13 = load i64, i64* %arrayidx8, align 8, !dbg !254
  %14 = load i64*, i64** %hash.addr, align 8, !dbg !255
  %arrayidx9 = getelementptr inbounds i64, i64* %14, i64 3, !dbg !255
  %15 = load i64, i64* %arrayidx9, align 8, !dbg !256
  %xor10 = xor i64 %15, %13, !dbg !256
  store i64 %xor10, i64* %arrayidx9, align 8, !dbg !256
  %16 = load i64*, i64** %block.addr, align 8, !dbg !257
  %arrayidx11 = getelementptr inbounds i64, i64* %16, i64 4, !dbg !257
  %17 = load i64, i64* %arrayidx11, align 8, !dbg !257
  %18 = load i64*, i64** %hash.addr, align 8, !dbg !258
  %arrayidx12 = getelementptr inbounds i64, i64* %18, i64 4, !dbg !258
  %19 = load i64, i64* %arrayidx12, align 8, !dbg !259
  %xor13 = xor i64 %19, %17, !dbg !259
  store i64 %xor13, i64* %arrayidx12, align 8, !dbg !259
  %20 = load i64*, i64** %block.addr, align 8, !dbg !260
  %arrayidx14 = getelementptr inbounds i64, i64* %20, i64 5, !dbg !260
  %21 = load i64, i64* %arrayidx14, align 8, !dbg !260
  %22 = load i64*, i64** %hash.addr, align 8, !dbg !261
  %arrayidx15 = getelementptr inbounds i64, i64* %22, i64 5, !dbg !261
  %23 = load i64, i64* %arrayidx15, align 8, !dbg !262
  %xor16 = xor i64 %23, %21, !dbg !262
  store i64 %xor16, i64* %arrayidx15, align 8, !dbg !262
  %24 = load i64*, i64** %block.addr, align 8, !dbg !263
  %arrayidx17 = getelementptr inbounds i64, i64* %24, i64 6, !dbg !263
  %25 = load i64, i64* %arrayidx17, align 8, !dbg !263
  %26 = load i64*, i64** %hash.addr, align 8, !dbg !264
  %arrayidx18 = getelementptr inbounds i64, i64* %26, i64 6, !dbg !264
  %27 = load i64, i64* %arrayidx18, align 8, !dbg !265
  %xor19 = xor i64 %27, %25, !dbg !265
  store i64 %xor19, i64* %arrayidx18, align 8, !dbg !265
  %28 = load i64*, i64** %block.addr, align 8, !dbg !266
  %arrayidx20 = getelementptr inbounds i64, i64* %28, i64 7, !dbg !266
  %29 = load i64, i64* %arrayidx20, align 8, !dbg !266
  %30 = load i64*, i64** %hash.addr, align 8, !dbg !267
  %arrayidx21 = getelementptr inbounds i64, i64* %30, i64 7, !dbg !267
  %31 = load i64, i64* %arrayidx21, align 8, !dbg !268
  %xor22 = xor i64 %31, %29, !dbg !268
  store i64 %xor22, i64* %arrayidx21, align 8, !dbg !268
  %32 = load i64*, i64** %block.addr, align 8, !dbg !269
  %arrayidx23 = getelementptr inbounds i64, i64* %32, i64 8, !dbg !269
  %33 = load i64, i64* %arrayidx23, align 8, !dbg !269
  %34 = load i64*, i64** %hash.addr, align 8, !dbg !270
  %arrayidx24 = getelementptr inbounds i64, i64* %34, i64 8, !dbg !270
  %35 = load i64, i64* %arrayidx24, align 8, !dbg !271
  %xor25 = xor i64 %35, %33, !dbg !271
  store i64 %xor25, i64* %arrayidx24, align 8, !dbg !271
  %36 = load i64, i64* %block_size.addr, align 8, !dbg !272
  %cmp = icmp ugt i64 %36, 72, !dbg !274
  br i1 %cmp, label %if.then, label %if.end58, !dbg !275

if.then:                                          ; preds = %entry
  %37 = load i64*, i64** %block.addr, align 8, !dbg !276
  %arrayidx26 = getelementptr inbounds i64, i64* %37, i64 9, !dbg !276
  %38 = load i64, i64* %arrayidx26, align 8, !dbg !276
  %39 = load i64*, i64** %hash.addr, align 8, !dbg !278
  %arrayidx27 = getelementptr inbounds i64, i64* %39, i64 9, !dbg !278
  %40 = load i64, i64* %arrayidx27, align 8, !dbg !279
  %xor28 = xor i64 %40, %38, !dbg !279
  store i64 %xor28, i64* %arrayidx27, align 8, !dbg !279
  %41 = load i64*, i64** %block.addr, align 8, !dbg !280
  %arrayidx29 = getelementptr inbounds i64, i64* %41, i64 10, !dbg !280
  %42 = load i64, i64* %arrayidx29, align 8, !dbg !280
  %43 = load i64*, i64** %hash.addr, align 8, !dbg !281
  %arrayidx30 = getelementptr inbounds i64, i64* %43, i64 10, !dbg !281
  %44 = load i64, i64* %arrayidx30, align 8, !dbg !282
  %xor31 = xor i64 %44, %42, !dbg !282
  store i64 %xor31, i64* %arrayidx30, align 8, !dbg !282
  %45 = load i64*, i64** %block.addr, align 8, !dbg !283
  %arrayidx32 = getelementptr inbounds i64, i64* %45, i64 11, !dbg !283
  %46 = load i64, i64* %arrayidx32, align 8, !dbg !283
  %47 = load i64*, i64** %hash.addr, align 8, !dbg !284
  %arrayidx33 = getelementptr inbounds i64, i64* %47, i64 11, !dbg !284
  %48 = load i64, i64* %arrayidx33, align 8, !dbg !285
  %xor34 = xor i64 %48, %46, !dbg !285
  store i64 %xor34, i64* %arrayidx33, align 8, !dbg !285
  %49 = load i64*, i64** %block.addr, align 8, !dbg !286
  %arrayidx35 = getelementptr inbounds i64, i64* %49, i64 12, !dbg !286
  %50 = load i64, i64* %arrayidx35, align 8, !dbg !286
  %51 = load i64*, i64** %hash.addr, align 8, !dbg !287
  %arrayidx36 = getelementptr inbounds i64, i64* %51, i64 12, !dbg !287
  %52 = load i64, i64* %arrayidx36, align 8, !dbg !288
  %xor37 = xor i64 %52, %50, !dbg !288
  store i64 %xor37, i64* %arrayidx36, align 8, !dbg !288
  %53 = load i64, i64* %block_size.addr, align 8, !dbg !289
  %cmp38 = icmp ugt i64 %53, 104, !dbg !291
  br i1 %cmp38, label %if.then39, label %if.end57, !dbg !292

if.then39:                                        ; preds = %if.then
  %54 = load i64*, i64** %block.addr, align 8, !dbg !293
  %arrayidx40 = getelementptr inbounds i64, i64* %54, i64 13, !dbg !293
  %55 = load i64, i64* %arrayidx40, align 8, !dbg !293
  %56 = load i64*, i64** %hash.addr, align 8, !dbg !295
  %arrayidx41 = getelementptr inbounds i64, i64* %56, i64 13, !dbg !295
  %57 = load i64, i64* %arrayidx41, align 8, !dbg !296
  %xor42 = xor i64 %57, %55, !dbg !296
  store i64 %xor42, i64* %arrayidx41, align 8, !dbg !296
  %58 = load i64*, i64** %block.addr, align 8, !dbg !297
  %arrayidx43 = getelementptr inbounds i64, i64* %58, i64 14, !dbg !297
  %59 = load i64, i64* %arrayidx43, align 8, !dbg !297
  %60 = load i64*, i64** %hash.addr, align 8, !dbg !298
  %arrayidx44 = getelementptr inbounds i64, i64* %60, i64 14, !dbg !298
  %61 = load i64, i64* %arrayidx44, align 8, !dbg !299
  %xor45 = xor i64 %61, %59, !dbg !299
  store i64 %xor45, i64* %arrayidx44, align 8, !dbg !299
  %62 = load i64*, i64** %block.addr, align 8, !dbg !300
  %arrayidx46 = getelementptr inbounds i64, i64* %62, i64 15, !dbg !300
  %63 = load i64, i64* %arrayidx46, align 8, !dbg !300
  %64 = load i64*, i64** %hash.addr, align 8, !dbg !301
  %arrayidx47 = getelementptr inbounds i64, i64* %64, i64 15, !dbg !301
  %65 = load i64, i64* %arrayidx47, align 8, !dbg !302
  %xor48 = xor i64 %65, %63, !dbg !302
  store i64 %xor48, i64* %arrayidx47, align 8, !dbg !302
  %66 = load i64*, i64** %block.addr, align 8, !dbg !303
  %arrayidx49 = getelementptr inbounds i64, i64* %66, i64 16, !dbg !303
  %67 = load i64, i64* %arrayidx49, align 8, !dbg !303
  %68 = load i64*, i64** %hash.addr, align 8, !dbg !304
  %arrayidx50 = getelementptr inbounds i64, i64* %68, i64 16, !dbg !304
  %69 = load i64, i64* %arrayidx50, align 8, !dbg !305
  %xor51 = xor i64 %69, %67, !dbg !305
  store i64 %xor51, i64* %arrayidx50, align 8, !dbg !305
  %70 = load i64, i64* %block_size.addr, align 8, !dbg !306
  %cmp52 = icmp ugt i64 %70, 136, !dbg !308
  br i1 %cmp52, label %if.then53, label %if.end, !dbg !309

if.then53:                                        ; preds = %if.then39
  %71 = load i64*, i64** %block.addr, align 8, !dbg !310
  %arrayidx54 = getelementptr inbounds i64, i64* %71, i64 17, !dbg !310
  %72 = load i64, i64* %arrayidx54, align 8, !dbg !310
  %73 = load i64*, i64** %hash.addr, align 8, !dbg !312
  %arrayidx55 = getelementptr inbounds i64, i64* %73, i64 17, !dbg !312
  %74 = load i64, i64* %arrayidx55, align 8, !dbg !313
  %xor56 = xor i64 %74, %72, !dbg !313
  store i64 %xor56, i64* %arrayidx55, align 8, !dbg !313
  br label %if.end, !dbg !314

if.end:                                           ; preds = %if.then53, %if.then39
  br label %if.end57, !dbg !315

if.end57:                                         ; preds = %if.end, %if.then
  br label %if.end58, !dbg !316

if.end58:                                         ; preds = %if.end57, %entry
  %75 = load i64*, i64** %hash.addr, align 8, !dbg !317
  call void @rhash_sha3_permutation(i64* %75), !dbg !318
  ret void, !dbg !319
}

; Function Attrs: nounwind uwtable
define void @rhash_sha3_final(%struct.sha3_ctx* %ctx, i8* %result) #0 !dbg !43 {
entry:
  %ctx.addr = alloca %struct.sha3_ctx*, align 8
  %result.addr = alloca i8*, align 8
  %digest_length = alloca i64, align 8
  %block_size1 = alloca i64, align 8
  store %struct.sha3_ctx* %ctx, %struct.sha3_ctx** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sha3_ctx** %ctx.addr, metadata !320, metadata !67), !dbg !321
  store i8* %result, i8** %result.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %result.addr, metadata !322, metadata !67), !dbg !323
  call void @llvm.dbg.declare(metadata i64* %digest_length, metadata !324, metadata !67), !dbg !325
  %0 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !326
  %block_size = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %0, i32 0, i32 3, !dbg !327
  %1 = load i32, i32* %block_size, align 4, !dbg !327
  %div = udiv i32 %1, 2, !dbg !328
  %sub = sub i32 100, %div, !dbg !329
  %conv = zext i32 %sub to i64, !dbg !330
  store i64 %conv, i64* %digest_length, align 8, !dbg !325
  call void @llvm.dbg.declare(metadata i64* %block_size1, metadata !331, metadata !67), !dbg !333
  %2 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !334
  %block_size2 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %2, i32 0, i32 3, !dbg !335
  %3 = load i32, i32* %block_size2, align 4, !dbg !335
  %conv3 = zext i32 %3 to i64, !dbg !334
  store i64 %conv3, i64* %block_size1, align 8, !dbg !333
  %4 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !336
  %rest = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %4, i32 0, i32 2, !dbg !338
  %5 = load i32, i32* %rest, align 8, !dbg !338
  %and = and i32 %5, -2147483648, !dbg !339
  %tobool = icmp ne i32 %and, 0, !dbg !339
  br i1 %tobool, label %if.end, label %if.then, !dbg !340

if.then:                                          ; preds = %entry
  %6 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !341
  %message = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %6, i32 0, i32 1, !dbg !343
  %arraydecay = getelementptr inbounds [24 x i64], [24 x i64]* %message, i32 0, i32 0, !dbg !341
  %7 = bitcast i64* %arraydecay to i8*, !dbg !344
  %8 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !345
  %rest4 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %8, i32 0, i32 2, !dbg !346
  %9 = load i32, i32* %rest4, align 8, !dbg !346
  %idx.ext = zext i32 %9 to i64, !dbg !347
  %add.ptr = getelementptr inbounds i8, i8* %7, i64 %idx.ext, !dbg !347
  %10 = load i64, i64* %block_size1, align 8, !dbg !348
  %11 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !349
  %rest5 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %11, i32 0, i32 2, !dbg !350
  %12 = load i32, i32* %rest5, align 8, !dbg !350
  %conv6 = zext i32 %12 to i64, !dbg !349
  %sub7 = sub i64 %10, %conv6, !dbg !351
  call void @llvm.memset.p0i8.i64(i8* %add.ptr, i8 0, i64 %sub7, i32 1, i1 false), !dbg !352
  %13 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !353
  %rest8 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %13, i32 0, i32 2, !dbg !354
  %14 = load i32, i32* %rest8, align 8, !dbg !354
  %idxprom = zext i32 %14 to i64, !dbg !355
  %15 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !356
  %message9 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %15, i32 0, i32 1, !dbg !357
  %arraydecay10 = getelementptr inbounds [24 x i64], [24 x i64]* %message9, i32 0, i32 0, !dbg !355
  %16 = bitcast i64* %arraydecay10 to i8*, !dbg !355
  %arrayidx = getelementptr inbounds i8, i8* %16, i64 %idxprom, !dbg !355
  %17 = load i8, i8* %arrayidx, align 1, !dbg !358
  %conv11 = sext i8 %17 to i32, !dbg !358
  %or = or i32 %conv11, 6, !dbg !358
  %conv12 = trunc i32 %or to i8, !dbg !358
  store i8 %conv12, i8* %arrayidx, align 1, !dbg !358
  %18 = load i64, i64* %block_size1, align 8, !dbg !359
  %sub13 = sub i64 %18, 1, !dbg !360
  %19 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !361
  %message14 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %19, i32 0, i32 1, !dbg !362
  %arraydecay15 = getelementptr inbounds [24 x i64], [24 x i64]* %message14, i32 0, i32 0, !dbg !363
  %20 = bitcast i64* %arraydecay15 to i8*, !dbg !363
  %arrayidx16 = getelementptr inbounds i8, i8* %20, i64 %sub13, !dbg !363
  %21 = load i8, i8* %arrayidx16, align 1, !dbg !364
  %conv17 = sext i8 %21 to i32, !dbg !364
  %or18 = or i32 %conv17, 128, !dbg !364
  %conv19 = trunc i32 %or18 to i8, !dbg !364
  store i8 %conv19, i8* %arrayidx16, align 1, !dbg !364
  %22 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !365
  %hash = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %22, i32 0, i32 0, !dbg !366
  %arraydecay20 = getelementptr inbounds [25 x i64], [25 x i64]* %hash, i32 0, i32 0, !dbg !365
  %23 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !367
  %message21 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %23, i32 0, i32 1, !dbg !368
  %arraydecay22 = getelementptr inbounds [24 x i64], [24 x i64]* %message21, i32 0, i32 0, !dbg !367
  %24 = load i64, i64* %block_size1, align 8, !dbg !369
  call void @rhash_sha3_process_block(i64* %arraydecay20, i64* %arraydecay22, i64 %24), !dbg !370
  %25 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !371
  %rest23 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %25, i32 0, i32 2, !dbg !372
  store i32 -2147483648, i32* %rest23, align 8, !dbg !373
  br label %if.end, !dbg !374

if.end:                                           ; preds = %if.then, %entry
  %26 = load i64, i64* %block_size1, align 8, !dbg !375
  %27 = load i64, i64* %digest_length, align 8, !dbg !375
  %cmp = icmp ugt i64 %26, %27, !dbg !375
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !375

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !376

cond.false:                                       ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.1, i32 0, i32 0), i32 325, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @__PRETTY_FUNCTION__.rhash_sha3_final, i32 0, i32 0)) #4, !dbg !378
  unreachable, !dbg !378
                                                  ; No predecessors!
  br label %cond.end, !dbg !380

cond.end:                                         ; preds = %28, %cond.true
  %29 = load i8*, i8** %result.addr, align 8, !dbg !382
  %tobool25 = icmp ne i8* %29, null, !dbg !382
  br i1 %tobool25, label %if.then26, label %if.end29, !dbg !384

if.then26:                                        ; preds = %cond.end
  %30 = load i8*, i8** %result.addr, align 8, !dbg !385
  %31 = load %struct.sha3_ctx*, %struct.sha3_ctx** %ctx.addr, align 8, !dbg !385
  %hash27 = getelementptr inbounds %struct.sha3_ctx, %struct.sha3_ctx* %31, i32 0, i32 0, !dbg !385
  %arraydecay28 = getelementptr inbounds [25 x i64], [25 x i64]* %hash27, i32 0, i32 0, !dbg !385
  %32 = bitcast i64* %arraydecay28 to i8*, !dbg !385
  %33 = load i64, i64* %digest_length, align 8, !dbg !385
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %30, i8* %32, i64 %33, i32 1, i1 false), !dbg !385
  br label %if.end29, !dbg !385

if.end29:                                         ; preds = %if.then26, %cond.end
  ret void, !dbg !387
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #3

; Function Attrs: nounwind uwtable
define internal void @rhash_sha3_permutation(i64* %state) #0 !dbg !55 {
entry:
  %state.addr = alloca i64*, align 8
  %round = alloca i32, align 4
  store i64* %state, i64** %state.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %state.addr, metadata !388, metadata !67), !dbg !389
  call void @llvm.dbg.declare(metadata i32* %round, metadata !390, metadata !67), !dbg !392
  store i32 0, i32* %round, align 4, !dbg !393
  br label %for.cond, !dbg !395

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %round, align 4, !dbg !396
  %cmp = icmp slt i32 %0, 24, !dbg !399
  br i1 %cmp, label %for.body, label %for.end, !dbg !400

for.body:                                         ; preds = %for.cond
  %1 = load i64*, i64** %state.addr, align 8, !dbg !401
  call void @keccak_theta(i64* %1), !dbg !403
  %2 = load i64*, i64** %state.addr, align 8, !dbg !404
  %arrayidx = getelementptr inbounds i64, i64* %2, i64 1, !dbg !404
  %3 = load i64, i64* %arrayidx, align 8, !dbg !404
  %shl = shl i64 %3, 1, !dbg !404
  %4 = load i64*, i64** %state.addr, align 8, !dbg !404
  %arrayidx1 = getelementptr inbounds i64, i64* %4, i64 1, !dbg !404
  %5 = load i64, i64* %arrayidx1, align 8, !dbg !404
  %shr = lshr i64 %5, 63, !dbg !404
  %xor = xor i64 %shl, %shr, !dbg !404
  %6 = load i64*, i64** %state.addr, align 8, !dbg !405
  %arrayidx2 = getelementptr inbounds i64, i64* %6, i64 1, !dbg !405
  store i64 %xor, i64* %arrayidx2, align 8, !dbg !406
  %7 = load i64*, i64** %state.addr, align 8, !dbg !407
  %arrayidx3 = getelementptr inbounds i64, i64* %7, i64 2, !dbg !407
  %8 = load i64, i64* %arrayidx3, align 8, !dbg !407
  %shl4 = shl i64 %8, 62, !dbg !407
  %9 = load i64*, i64** %state.addr, align 8, !dbg !407
  %arrayidx5 = getelementptr inbounds i64, i64* %9, i64 2, !dbg !407
  %10 = load i64, i64* %arrayidx5, align 8, !dbg !407
  %shr6 = lshr i64 %10, 2, !dbg !407
  %xor7 = xor i64 %shl4, %shr6, !dbg !407
  %11 = load i64*, i64** %state.addr, align 8, !dbg !408
  %arrayidx8 = getelementptr inbounds i64, i64* %11, i64 2, !dbg !408
  store i64 %xor7, i64* %arrayidx8, align 8, !dbg !409
  %12 = load i64*, i64** %state.addr, align 8, !dbg !410
  %arrayidx9 = getelementptr inbounds i64, i64* %12, i64 3, !dbg !410
  %13 = load i64, i64* %arrayidx9, align 8, !dbg !410
  %shl10 = shl i64 %13, 28, !dbg !410
  %14 = load i64*, i64** %state.addr, align 8, !dbg !410
  %arrayidx11 = getelementptr inbounds i64, i64* %14, i64 3, !dbg !410
  %15 = load i64, i64* %arrayidx11, align 8, !dbg !410
  %shr12 = lshr i64 %15, 36, !dbg !410
  %xor13 = xor i64 %shl10, %shr12, !dbg !410
  %16 = load i64*, i64** %state.addr, align 8, !dbg !411
  %arrayidx14 = getelementptr inbounds i64, i64* %16, i64 3, !dbg !411
  store i64 %xor13, i64* %arrayidx14, align 8, !dbg !412
  %17 = load i64*, i64** %state.addr, align 8, !dbg !413
  %arrayidx15 = getelementptr inbounds i64, i64* %17, i64 4, !dbg !413
  %18 = load i64, i64* %arrayidx15, align 8, !dbg !413
  %shl16 = shl i64 %18, 27, !dbg !413
  %19 = load i64*, i64** %state.addr, align 8, !dbg !413
  %arrayidx17 = getelementptr inbounds i64, i64* %19, i64 4, !dbg !413
  %20 = load i64, i64* %arrayidx17, align 8, !dbg !413
  %shr18 = lshr i64 %20, 37, !dbg !413
  %xor19 = xor i64 %shl16, %shr18, !dbg !413
  %21 = load i64*, i64** %state.addr, align 8, !dbg !414
  %arrayidx20 = getelementptr inbounds i64, i64* %21, i64 4, !dbg !414
  store i64 %xor19, i64* %arrayidx20, align 8, !dbg !415
  %22 = load i64*, i64** %state.addr, align 8, !dbg !416
  %arrayidx21 = getelementptr inbounds i64, i64* %22, i64 5, !dbg !416
  %23 = load i64, i64* %arrayidx21, align 8, !dbg !416
  %shl22 = shl i64 %23, 36, !dbg !416
  %24 = load i64*, i64** %state.addr, align 8, !dbg !416
  %arrayidx23 = getelementptr inbounds i64, i64* %24, i64 5, !dbg !416
  %25 = load i64, i64* %arrayidx23, align 8, !dbg !416
  %shr24 = lshr i64 %25, 28, !dbg !416
  %xor25 = xor i64 %shl22, %shr24, !dbg !416
  %26 = load i64*, i64** %state.addr, align 8, !dbg !417
  %arrayidx26 = getelementptr inbounds i64, i64* %26, i64 5, !dbg !417
  store i64 %xor25, i64* %arrayidx26, align 8, !dbg !418
  %27 = load i64*, i64** %state.addr, align 8, !dbg !419
  %arrayidx27 = getelementptr inbounds i64, i64* %27, i64 6, !dbg !419
  %28 = load i64, i64* %arrayidx27, align 8, !dbg !419
  %shl28 = shl i64 %28, 44, !dbg !419
  %29 = load i64*, i64** %state.addr, align 8, !dbg !419
  %arrayidx29 = getelementptr inbounds i64, i64* %29, i64 6, !dbg !419
  %30 = load i64, i64* %arrayidx29, align 8, !dbg !419
  %shr30 = lshr i64 %30, 20, !dbg !419
  %xor31 = xor i64 %shl28, %shr30, !dbg !419
  %31 = load i64*, i64** %state.addr, align 8, !dbg !420
  %arrayidx32 = getelementptr inbounds i64, i64* %31, i64 6, !dbg !420
  store i64 %xor31, i64* %arrayidx32, align 8, !dbg !421
  %32 = load i64*, i64** %state.addr, align 8, !dbg !422
  %arrayidx33 = getelementptr inbounds i64, i64* %32, i64 7, !dbg !422
  %33 = load i64, i64* %arrayidx33, align 8, !dbg !422
  %shl34 = shl i64 %33, 6, !dbg !422
  %34 = load i64*, i64** %state.addr, align 8, !dbg !422
  %arrayidx35 = getelementptr inbounds i64, i64* %34, i64 7, !dbg !422
  %35 = load i64, i64* %arrayidx35, align 8, !dbg !422
  %shr36 = lshr i64 %35, 58, !dbg !422
  %xor37 = xor i64 %shl34, %shr36, !dbg !422
  %36 = load i64*, i64** %state.addr, align 8, !dbg !423
  %arrayidx38 = getelementptr inbounds i64, i64* %36, i64 7, !dbg !423
  store i64 %xor37, i64* %arrayidx38, align 8, !dbg !424
  %37 = load i64*, i64** %state.addr, align 8, !dbg !425
  %arrayidx39 = getelementptr inbounds i64, i64* %37, i64 8, !dbg !425
  %38 = load i64, i64* %arrayidx39, align 8, !dbg !425
  %shl40 = shl i64 %38, 55, !dbg !425
  %39 = load i64*, i64** %state.addr, align 8, !dbg !425
  %arrayidx41 = getelementptr inbounds i64, i64* %39, i64 8, !dbg !425
  %40 = load i64, i64* %arrayidx41, align 8, !dbg !425
  %shr42 = lshr i64 %40, 9, !dbg !425
  %xor43 = xor i64 %shl40, %shr42, !dbg !425
  %41 = load i64*, i64** %state.addr, align 8, !dbg !426
  %arrayidx44 = getelementptr inbounds i64, i64* %41, i64 8, !dbg !426
  store i64 %xor43, i64* %arrayidx44, align 8, !dbg !427
  %42 = load i64*, i64** %state.addr, align 8, !dbg !428
  %arrayidx45 = getelementptr inbounds i64, i64* %42, i64 9, !dbg !428
  %43 = load i64, i64* %arrayidx45, align 8, !dbg !428
  %shl46 = shl i64 %43, 20, !dbg !428
  %44 = load i64*, i64** %state.addr, align 8, !dbg !428
  %arrayidx47 = getelementptr inbounds i64, i64* %44, i64 9, !dbg !428
  %45 = load i64, i64* %arrayidx47, align 8, !dbg !428
  %shr48 = lshr i64 %45, 44, !dbg !428
  %xor49 = xor i64 %shl46, %shr48, !dbg !428
  %46 = load i64*, i64** %state.addr, align 8, !dbg !429
  %arrayidx50 = getelementptr inbounds i64, i64* %46, i64 9, !dbg !429
  store i64 %xor49, i64* %arrayidx50, align 8, !dbg !430
  %47 = load i64*, i64** %state.addr, align 8, !dbg !431
  %arrayidx51 = getelementptr inbounds i64, i64* %47, i64 10, !dbg !431
  %48 = load i64, i64* %arrayidx51, align 8, !dbg !431
  %shl52 = shl i64 %48, 3, !dbg !431
  %49 = load i64*, i64** %state.addr, align 8, !dbg !431
  %arrayidx53 = getelementptr inbounds i64, i64* %49, i64 10, !dbg !431
  %50 = load i64, i64* %arrayidx53, align 8, !dbg !431
  %shr54 = lshr i64 %50, 61, !dbg !431
  %xor55 = xor i64 %shl52, %shr54, !dbg !431
  %51 = load i64*, i64** %state.addr, align 8, !dbg !432
  %arrayidx56 = getelementptr inbounds i64, i64* %51, i64 10, !dbg !432
  store i64 %xor55, i64* %arrayidx56, align 8, !dbg !433
  %52 = load i64*, i64** %state.addr, align 8, !dbg !434
  %arrayidx57 = getelementptr inbounds i64, i64* %52, i64 11, !dbg !434
  %53 = load i64, i64* %arrayidx57, align 8, !dbg !434
  %shl58 = shl i64 %53, 10, !dbg !434
  %54 = load i64*, i64** %state.addr, align 8, !dbg !434
  %arrayidx59 = getelementptr inbounds i64, i64* %54, i64 11, !dbg !434
  %55 = load i64, i64* %arrayidx59, align 8, !dbg !434
  %shr60 = lshr i64 %55, 54, !dbg !434
  %xor61 = xor i64 %shl58, %shr60, !dbg !434
  %56 = load i64*, i64** %state.addr, align 8, !dbg !435
  %arrayidx62 = getelementptr inbounds i64, i64* %56, i64 11, !dbg !435
  store i64 %xor61, i64* %arrayidx62, align 8, !dbg !436
  %57 = load i64*, i64** %state.addr, align 8, !dbg !437
  %arrayidx63 = getelementptr inbounds i64, i64* %57, i64 12, !dbg !437
  %58 = load i64, i64* %arrayidx63, align 8, !dbg !437
  %shl64 = shl i64 %58, 43, !dbg !437
  %59 = load i64*, i64** %state.addr, align 8, !dbg !437
  %arrayidx65 = getelementptr inbounds i64, i64* %59, i64 12, !dbg !437
  %60 = load i64, i64* %arrayidx65, align 8, !dbg !437
  %shr66 = lshr i64 %60, 21, !dbg !437
  %xor67 = xor i64 %shl64, %shr66, !dbg !437
  %61 = load i64*, i64** %state.addr, align 8, !dbg !438
  %arrayidx68 = getelementptr inbounds i64, i64* %61, i64 12, !dbg !438
  store i64 %xor67, i64* %arrayidx68, align 8, !dbg !439
  %62 = load i64*, i64** %state.addr, align 8, !dbg !440
  %arrayidx69 = getelementptr inbounds i64, i64* %62, i64 13, !dbg !440
  %63 = load i64, i64* %arrayidx69, align 8, !dbg !440
  %shl70 = shl i64 %63, 25, !dbg !440
  %64 = load i64*, i64** %state.addr, align 8, !dbg !440
  %arrayidx71 = getelementptr inbounds i64, i64* %64, i64 13, !dbg !440
  %65 = load i64, i64* %arrayidx71, align 8, !dbg !440
  %shr72 = lshr i64 %65, 39, !dbg !440
  %xor73 = xor i64 %shl70, %shr72, !dbg !440
  %66 = load i64*, i64** %state.addr, align 8, !dbg !441
  %arrayidx74 = getelementptr inbounds i64, i64* %66, i64 13, !dbg !441
  store i64 %xor73, i64* %arrayidx74, align 8, !dbg !442
  %67 = load i64*, i64** %state.addr, align 8, !dbg !443
  %arrayidx75 = getelementptr inbounds i64, i64* %67, i64 14, !dbg !443
  %68 = load i64, i64* %arrayidx75, align 8, !dbg !443
  %shl76 = shl i64 %68, 39, !dbg !443
  %69 = load i64*, i64** %state.addr, align 8, !dbg !443
  %arrayidx77 = getelementptr inbounds i64, i64* %69, i64 14, !dbg !443
  %70 = load i64, i64* %arrayidx77, align 8, !dbg !443
  %shr78 = lshr i64 %70, 25, !dbg !443
  %xor79 = xor i64 %shl76, %shr78, !dbg !443
  %71 = load i64*, i64** %state.addr, align 8, !dbg !444
  %arrayidx80 = getelementptr inbounds i64, i64* %71, i64 14, !dbg !444
  store i64 %xor79, i64* %arrayidx80, align 8, !dbg !445
  %72 = load i64*, i64** %state.addr, align 8, !dbg !446
  %arrayidx81 = getelementptr inbounds i64, i64* %72, i64 15, !dbg !446
  %73 = load i64, i64* %arrayidx81, align 8, !dbg !446
  %shl82 = shl i64 %73, 41, !dbg !446
  %74 = load i64*, i64** %state.addr, align 8, !dbg !446
  %arrayidx83 = getelementptr inbounds i64, i64* %74, i64 15, !dbg !446
  %75 = load i64, i64* %arrayidx83, align 8, !dbg !446
  %shr84 = lshr i64 %75, 23, !dbg !446
  %xor85 = xor i64 %shl82, %shr84, !dbg !446
  %76 = load i64*, i64** %state.addr, align 8, !dbg !447
  %arrayidx86 = getelementptr inbounds i64, i64* %76, i64 15, !dbg !447
  store i64 %xor85, i64* %arrayidx86, align 8, !dbg !448
  %77 = load i64*, i64** %state.addr, align 8, !dbg !449
  %arrayidx87 = getelementptr inbounds i64, i64* %77, i64 16, !dbg !449
  %78 = load i64, i64* %arrayidx87, align 8, !dbg !449
  %shl88 = shl i64 %78, 45, !dbg !449
  %79 = load i64*, i64** %state.addr, align 8, !dbg !449
  %arrayidx89 = getelementptr inbounds i64, i64* %79, i64 16, !dbg !449
  %80 = load i64, i64* %arrayidx89, align 8, !dbg !449
  %shr90 = lshr i64 %80, 19, !dbg !449
  %xor91 = xor i64 %shl88, %shr90, !dbg !449
  %81 = load i64*, i64** %state.addr, align 8, !dbg !450
  %arrayidx92 = getelementptr inbounds i64, i64* %81, i64 16, !dbg !450
  store i64 %xor91, i64* %arrayidx92, align 8, !dbg !451
  %82 = load i64*, i64** %state.addr, align 8, !dbg !452
  %arrayidx93 = getelementptr inbounds i64, i64* %82, i64 17, !dbg !452
  %83 = load i64, i64* %arrayidx93, align 8, !dbg !452
  %shl94 = shl i64 %83, 15, !dbg !452
  %84 = load i64*, i64** %state.addr, align 8, !dbg !452
  %arrayidx95 = getelementptr inbounds i64, i64* %84, i64 17, !dbg !452
  %85 = load i64, i64* %arrayidx95, align 8, !dbg !452
  %shr96 = lshr i64 %85, 49, !dbg !452
  %xor97 = xor i64 %shl94, %shr96, !dbg !452
  %86 = load i64*, i64** %state.addr, align 8, !dbg !453
  %arrayidx98 = getelementptr inbounds i64, i64* %86, i64 17, !dbg !453
  store i64 %xor97, i64* %arrayidx98, align 8, !dbg !454
  %87 = load i64*, i64** %state.addr, align 8, !dbg !455
  %arrayidx99 = getelementptr inbounds i64, i64* %87, i64 18, !dbg !455
  %88 = load i64, i64* %arrayidx99, align 8, !dbg !455
  %shl100 = shl i64 %88, 21, !dbg !455
  %89 = load i64*, i64** %state.addr, align 8, !dbg !455
  %arrayidx101 = getelementptr inbounds i64, i64* %89, i64 18, !dbg !455
  %90 = load i64, i64* %arrayidx101, align 8, !dbg !455
  %shr102 = lshr i64 %90, 43, !dbg !455
  %xor103 = xor i64 %shl100, %shr102, !dbg !455
  %91 = load i64*, i64** %state.addr, align 8, !dbg !456
  %arrayidx104 = getelementptr inbounds i64, i64* %91, i64 18, !dbg !456
  store i64 %xor103, i64* %arrayidx104, align 8, !dbg !457
  %92 = load i64*, i64** %state.addr, align 8, !dbg !458
  %arrayidx105 = getelementptr inbounds i64, i64* %92, i64 19, !dbg !458
  %93 = load i64, i64* %arrayidx105, align 8, !dbg !458
  %shl106 = shl i64 %93, 8, !dbg !458
  %94 = load i64*, i64** %state.addr, align 8, !dbg !458
  %arrayidx107 = getelementptr inbounds i64, i64* %94, i64 19, !dbg !458
  %95 = load i64, i64* %arrayidx107, align 8, !dbg !458
  %shr108 = lshr i64 %95, 56, !dbg !458
  %xor109 = xor i64 %shl106, %shr108, !dbg !458
  %96 = load i64*, i64** %state.addr, align 8, !dbg !459
  %arrayidx110 = getelementptr inbounds i64, i64* %96, i64 19, !dbg !459
  store i64 %xor109, i64* %arrayidx110, align 8, !dbg !460
  %97 = load i64*, i64** %state.addr, align 8, !dbg !461
  %arrayidx111 = getelementptr inbounds i64, i64* %97, i64 20, !dbg !461
  %98 = load i64, i64* %arrayidx111, align 8, !dbg !461
  %shl112 = shl i64 %98, 18, !dbg !461
  %99 = load i64*, i64** %state.addr, align 8, !dbg !461
  %arrayidx113 = getelementptr inbounds i64, i64* %99, i64 20, !dbg !461
  %100 = load i64, i64* %arrayidx113, align 8, !dbg !461
  %shr114 = lshr i64 %100, 46, !dbg !461
  %xor115 = xor i64 %shl112, %shr114, !dbg !461
  %101 = load i64*, i64** %state.addr, align 8, !dbg !462
  %arrayidx116 = getelementptr inbounds i64, i64* %101, i64 20, !dbg !462
  store i64 %xor115, i64* %arrayidx116, align 8, !dbg !463
  %102 = load i64*, i64** %state.addr, align 8, !dbg !464
  %arrayidx117 = getelementptr inbounds i64, i64* %102, i64 21, !dbg !464
  %103 = load i64, i64* %arrayidx117, align 8, !dbg !464
  %shl118 = shl i64 %103, 2, !dbg !464
  %104 = load i64*, i64** %state.addr, align 8, !dbg !464
  %arrayidx119 = getelementptr inbounds i64, i64* %104, i64 21, !dbg !464
  %105 = load i64, i64* %arrayidx119, align 8, !dbg !464
  %shr120 = lshr i64 %105, 62, !dbg !464
  %xor121 = xor i64 %shl118, %shr120, !dbg !464
  %106 = load i64*, i64** %state.addr, align 8, !dbg !465
  %arrayidx122 = getelementptr inbounds i64, i64* %106, i64 21, !dbg !465
  store i64 %xor121, i64* %arrayidx122, align 8, !dbg !466
  %107 = load i64*, i64** %state.addr, align 8, !dbg !467
  %arrayidx123 = getelementptr inbounds i64, i64* %107, i64 22, !dbg !467
  %108 = load i64, i64* %arrayidx123, align 8, !dbg !467
  %shl124 = shl i64 %108, 61, !dbg !467
  %109 = load i64*, i64** %state.addr, align 8, !dbg !467
  %arrayidx125 = getelementptr inbounds i64, i64* %109, i64 22, !dbg !467
  %110 = load i64, i64* %arrayidx125, align 8, !dbg !467
  %shr126 = lshr i64 %110, 3, !dbg !467
  %xor127 = xor i64 %shl124, %shr126, !dbg !467
  %111 = load i64*, i64** %state.addr, align 8, !dbg !468
  %arrayidx128 = getelementptr inbounds i64, i64* %111, i64 22, !dbg !468
  store i64 %xor127, i64* %arrayidx128, align 8, !dbg !469
  %112 = load i64*, i64** %state.addr, align 8, !dbg !470
  %arrayidx129 = getelementptr inbounds i64, i64* %112, i64 23, !dbg !470
  %113 = load i64, i64* %arrayidx129, align 8, !dbg !470
  %shl130 = shl i64 %113, 56, !dbg !470
  %114 = load i64*, i64** %state.addr, align 8, !dbg !470
  %arrayidx131 = getelementptr inbounds i64, i64* %114, i64 23, !dbg !470
  %115 = load i64, i64* %arrayidx131, align 8, !dbg !470
  %shr132 = lshr i64 %115, 8, !dbg !470
  %xor133 = xor i64 %shl130, %shr132, !dbg !470
  %116 = load i64*, i64** %state.addr, align 8, !dbg !471
  %arrayidx134 = getelementptr inbounds i64, i64* %116, i64 23, !dbg !471
  store i64 %xor133, i64* %arrayidx134, align 8, !dbg !472
  %117 = load i64*, i64** %state.addr, align 8, !dbg !473
  %arrayidx135 = getelementptr inbounds i64, i64* %117, i64 24, !dbg !473
  %118 = load i64, i64* %arrayidx135, align 8, !dbg !473
  %shl136 = shl i64 %118, 14, !dbg !473
  %119 = load i64*, i64** %state.addr, align 8, !dbg !473
  %arrayidx137 = getelementptr inbounds i64, i64* %119, i64 24, !dbg !473
  %120 = load i64, i64* %arrayidx137, align 8, !dbg !473
  %shr138 = lshr i64 %120, 50, !dbg !473
  %xor139 = xor i64 %shl136, %shr138, !dbg !473
  %121 = load i64*, i64** %state.addr, align 8, !dbg !474
  %arrayidx140 = getelementptr inbounds i64, i64* %121, i64 24, !dbg !474
  store i64 %xor139, i64* %arrayidx140, align 8, !dbg !475
  %122 = load i64*, i64** %state.addr, align 8, !dbg !476
  call void @keccak_pi(i64* %122), !dbg !477
  %123 = load i64*, i64** %state.addr, align 8, !dbg !478
  call void @keccak_chi(i64* %123), !dbg !479
  %124 = load i32, i32* %round, align 4, !dbg !480
  %idxprom = sext i32 %124 to i64, !dbg !481
  %arrayidx141 = getelementptr inbounds [24 x i64], [24 x i64]* @keccak_round_constants, i64 0, i64 %idxprom, !dbg !481
  %125 = load i64, i64* %arrayidx141, align 8, !dbg !481
  %126 = load i64*, i64** %state.addr, align 8, !dbg !482
  %127 = load i64, i64* %126, align 8, !dbg !483
  %xor142 = xor i64 %127, %125, !dbg !483
  store i64 %xor142, i64* %126, align 8, !dbg !483
  br label %for.inc, !dbg !484

for.inc:                                          ; preds = %for.body
  %128 = load i32, i32* %round, align 4, !dbg !485
  %inc = add nsw i32 %128, 1, !dbg !485
  store i32 %inc, i32* %round, align 4, !dbg !485
  br label %for.cond, !dbg !487

for.end:                                          ; preds = %for.cond
  ret void, !dbg !488
}

; Function Attrs: nounwind uwtable
define internal void @keccak_theta(i64* %A) #0 !dbg !58 {
entry:
  %A.addr = alloca i64*, align 8
  %x = alloca i32, align 4
  %C = alloca [5 x i64], align 16
  %D = alloca [5 x i64], align 16
  store i64* %A, i64** %A.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %A.addr, metadata !489, metadata !67), !dbg !490
  call void @llvm.dbg.declare(metadata i32* %x, metadata !491, metadata !67), !dbg !492
  call void @llvm.dbg.declare(metadata [5 x i64]* %C, metadata !493, metadata !67), !dbg !497
  call void @llvm.dbg.declare(metadata [5 x i64]* %D, metadata !498, metadata !67), !dbg !499
  store i32 0, i32* %x, align 4, !dbg !500
  br label %for.cond, !dbg !502

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %x, align 4, !dbg !503
  %cmp = icmp ult i32 %0, 5, !dbg !506
  br i1 %cmp, label %for.body, label %for.end, !dbg !507

for.body:                                         ; preds = %for.cond
  %1 = load i32, i32* %x, align 4, !dbg !508
  %idxprom = zext i32 %1 to i64, !dbg !510
  %2 = load i64*, i64** %A.addr, align 8, !dbg !510
  %arrayidx = getelementptr inbounds i64, i64* %2, i64 %idxprom, !dbg !510
  %3 = load i64, i64* %arrayidx, align 8, !dbg !510
  %4 = load i32, i32* %x, align 4, !dbg !511
  %add = add i32 %4, 5, !dbg !512
  %idxprom1 = zext i32 %add to i64, !dbg !513
  %5 = load i64*, i64** %A.addr, align 8, !dbg !513
  %arrayidx2 = getelementptr inbounds i64, i64* %5, i64 %idxprom1, !dbg !513
  %6 = load i64, i64* %arrayidx2, align 8, !dbg !513
  %xor = xor i64 %3, %6, !dbg !514
  %7 = load i32, i32* %x, align 4, !dbg !515
  %add3 = add i32 %7, 10, !dbg !516
  %idxprom4 = zext i32 %add3 to i64, !dbg !517
  %8 = load i64*, i64** %A.addr, align 8, !dbg !517
  %arrayidx5 = getelementptr inbounds i64, i64* %8, i64 %idxprom4, !dbg !517
  %9 = load i64, i64* %arrayidx5, align 8, !dbg !517
  %xor6 = xor i64 %xor, %9, !dbg !518
  %10 = load i32, i32* %x, align 4, !dbg !519
  %add7 = add i32 %10, 15, !dbg !520
  %idxprom8 = zext i32 %add7 to i64, !dbg !521
  %11 = load i64*, i64** %A.addr, align 8, !dbg !521
  %arrayidx9 = getelementptr inbounds i64, i64* %11, i64 %idxprom8, !dbg !521
  %12 = load i64, i64* %arrayidx9, align 8, !dbg !521
  %xor10 = xor i64 %xor6, %12, !dbg !522
  %13 = load i32, i32* %x, align 4, !dbg !523
  %add11 = add i32 %13, 20, !dbg !524
  %idxprom12 = zext i32 %add11 to i64, !dbg !525
  %14 = load i64*, i64** %A.addr, align 8, !dbg !525
  %arrayidx13 = getelementptr inbounds i64, i64* %14, i64 %idxprom12, !dbg !525
  %15 = load i64, i64* %arrayidx13, align 8, !dbg !525
  %xor14 = xor i64 %xor10, %15, !dbg !526
  %16 = load i32, i32* %x, align 4, !dbg !527
  %idxprom15 = zext i32 %16 to i64, !dbg !528
  %arrayidx16 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 %idxprom15, !dbg !528
  store i64 %xor14, i64* %arrayidx16, align 8, !dbg !529
  br label %for.inc, !dbg !530

for.inc:                                          ; preds = %for.body
  %17 = load i32, i32* %x, align 4, !dbg !531
  %inc = add i32 %17, 1, !dbg !531
  store i32 %inc, i32* %x, align 4, !dbg !531
  br label %for.cond, !dbg !533

for.end:                                          ; preds = %for.cond
  %arrayidx17 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 1, !dbg !534
  %18 = load i64, i64* %arrayidx17, align 8, !dbg !534
  %shl = shl i64 %18, 1, !dbg !534
  %arrayidx18 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 1, !dbg !534
  %19 = load i64, i64* %arrayidx18, align 8, !dbg !534
  %shr = lshr i64 %19, 63, !dbg !534
  %xor19 = xor i64 %shl, %shr, !dbg !534
  %arrayidx20 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 4, !dbg !535
  %20 = load i64, i64* %arrayidx20, align 16, !dbg !535
  %xor21 = xor i64 %xor19, %20, !dbg !536
  %arrayidx22 = getelementptr inbounds [5 x i64], [5 x i64]* %D, i64 0, i64 0, !dbg !537
  store i64 %xor21, i64* %arrayidx22, align 16, !dbg !538
  %arrayidx23 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 2, !dbg !539
  %21 = load i64, i64* %arrayidx23, align 16, !dbg !539
  %shl24 = shl i64 %21, 1, !dbg !539
  %arrayidx25 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 2, !dbg !539
  %22 = load i64, i64* %arrayidx25, align 16, !dbg !539
  %shr26 = lshr i64 %22, 63, !dbg !539
  %xor27 = xor i64 %shl24, %shr26, !dbg !539
  %arrayidx28 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 0, !dbg !540
  %23 = load i64, i64* %arrayidx28, align 16, !dbg !540
  %xor29 = xor i64 %xor27, %23, !dbg !541
  %arrayidx30 = getelementptr inbounds [5 x i64], [5 x i64]* %D, i64 0, i64 1, !dbg !542
  store i64 %xor29, i64* %arrayidx30, align 8, !dbg !543
  %arrayidx31 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 3, !dbg !544
  %24 = load i64, i64* %arrayidx31, align 8, !dbg !544
  %shl32 = shl i64 %24, 1, !dbg !544
  %arrayidx33 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 3, !dbg !544
  %25 = load i64, i64* %arrayidx33, align 8, !dbg !544
  %shr34 = lshr i64 %25, 63, !dbg !544
  %xor35 = xor i64 %shl32, %shr34, !dbg !544
  %arrayidx36 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 1, !dbg !545
  %26 = load i64, i64* %arrayidx36, align 8, !dbg !545
  %xor37 = xor i64 %xor35, %26, !dbg !546
  %arrayidx38 = getelementptr inbounds [5 x i64], [5 x i64]* %D, i64 0, i64 2, !dbg !547
  store i64 %xor37, i64* %arrayidx38, align 16, !dbg !548
  %arrayidx39 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 4, !dbg !549
  %27 = load i64, i64* %arrayidx39, align 16, !dbg !549
  %shl40 = shl i64 %27, 1, !dbg !549
  %arrayidx41 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 4, !dbg !549
  %28 = load i64, i64* %arrayidx41, align 16, !dbg !549
  %shr42 = lshr i64 %28, 63, !dbg !549
  %xor43 = xor i64 %shl40, %shr42, !dbg !549
  %arrayidx44 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 2, !dbg !550
  %29 = load i64, i64* %arrayidx44, align 16, !dbg !550
  %xor45 = xor i64 %xor43, %29, !dbg !551
  %arrayidx46 = getelementptr inbounds [5 x i64], [5 x i64]* %D, i64 0, i64 3, !dbg !552
  store i64 %xor45, i64* %arrayidx46, align 8, !dbg !553
  %arrayidx47 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 0, !dbg !554
  %30 = load i64, i64* %arrayidx47, align 16, !dbg !554
  %shl48 = shl i64 %30, 1, !dbg !554
  %arrayidx49 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 0, !dbg !554
  %31 = load i64, i64* %arrayidx49, align 16, !dbg !554
  %shr50 = lshr i64 %31, 63, !dbg !554
  %xor51 = xor i64 %shl48, %shr50, !dbg !554
  %arrayidx52 = getelementptr inbounds [5 x i64], [5 x i64]* %C, i64 0, i64 3, !dbg !555
  %32 = load i64, i64* %arrayidx52, align 8, !dbg !555
  %xor53 = xor i64 %xor51, %32, !dbg !556
  %arrayidx54 = getelementptr inbounds [5 x i64], [5 x i64]* %D, i64 0, i64 4, !dbg !557
  store i64 %xor53, i64* %arrayidx54, align 16, !dbg !558
  store i32 0, i32* %x, align 4, !dbg !559
  br label %for.cond55, !dbg !561

for.cond55:                                       ; preds = %for.inc87, %for.end
  %33 = load i32, i32* %x, align 4, !dbg !562
  %cmp56 = icmp ult i32 %33, 5, !dbg !565
  br i1 %cmp56, label %for.body57, label %for.end89, !dbg !566

for.body57:                                       ; preds = %for.cond55
  %34 = load i32, i32* %x, align 4, !dbg !567
  %idxprom58 = zext i32 %34 to i64, !dbg !569
  %arrayidx59 = getelementptr inbounds [5 x i64], [5 x i64]* %D, i64 0, i64 %idxprom58, !dbg !569
  %35 = load i64, i64* %arrayidx59, align 8, !dbg !569
  %36 = load i32, i32* %x, align 4, !dbg !570
  %idxprom60 = zext i32 %36 to i64, !dbg !571
  %37 = load i64*, i64** %A.addr, align 8, !dbg !571
  %arrayidx61 = getelementptr inbounds i64, i64* %37, i64 %idxprom60, !dbg !571
  %38 = load i64, i64* %arrayidx61, align 8, !dbg !572
  %xor62 = xor i64 %38, %35, !dbg !572
  store i64 %xor62, i64* %arrayidx61, align 8, !dbg !572
  %39 = load i32, i32* %x, align 4, !dbg !573
  %idxprom63 = zext i32 %39 to i64, !dbg !574
  %arrayidx64 = getelementptr inbounds [5 x i64], [5 x i64]* %D, i64 0, i64 %idxprom63, !dbg !574
  %40 = load i64, i64* %arrayidx64, align 8, !dbg !574
  %41 = load i32, i32* %x, align 4, !dbg !575
  %add65 = add i32 %41, 5, !dbg !576
  %idxprom66 = zext i32 %add65 to i64, !dbg !577
  %42 = load i64*, i64** %A.addr, align 8, !dbg !577
  %arrayidx67 = getelementptr inbounds i64, i64* %42, i64 %idxprom66, !dbg !577
  %43 = load i64, i64* %arrayidx67, align 8, !dbg !578
  %xor68 = xor i64 %43, %40, !dbg !578
  store i64 %xor68, i64* %arrayidx67, align 8, !dbg !578
  %44 = load i32, i32* %x, align 4, !dbg !579
  %idxprom69 = zext i32 %44 to i64, !dbg !580
  %arrayidx70 = getelementptr inbounds [5 x i64], [5 x i64]* %D, i64 0, i64 %idxprom69, !dbg !580
  %45 = load i64, i64* %arrayidx70, align 8, !dbg !580
  %46 = load i32, i32* %x, align 4, !dbg !581
  %add71 = add i32 %46, 10, !dbg !582
  %idxprom72 = zext i32 %add71 to i64, !dbg !583
  %47 = load i64*, i64** %A.addr, align 8, !dbg !583
  %arrayidx73 = getelementptr inbounds i64, i64* %47, i64 %idxprom72, !dbg !583
  %48 = load i64, i64* %arrayidx73, align 8, !dbg !584
  %xor74 = xor i64 %48, %45, !dbg !584
  store i64 %xor74, i64* %arrayidx73, align 8, !dbg !584
  %49 = load i32, i32* %x, align 4, !dbg !585
  %idxprom75 = zext i32 %49 to i64, !dbg !586
  %arrayidx76 = getelementptr inbounds [5 x i64], [5 x i64]* %D, i64 0, i64 %idxprom75, !dbg !586
  %50 = load i64, i64* %arrayidx76, align 8, !dbg !586
  %51 = load i32, i32* %x, align 4, !dbg !587
  %add77 = add i32 %51, 15, !dbg !588
  %idxprom78 = zext i32 %add77 to i64, !dbg !589
  %52 = load i64*, i64** %A.addr, align 8, !dbg !589
  %arrayidx79 = getelementptr inbounds i64, i64* %52, i64 %idxprom78, !dbg !589
  %53 = load i64, i64* %arrayidx79, align 8, !dbg !590
  %xor80 = xor i64 %53, %50, !dbg !590
  store i64 %xor80, i64* %arrayidx79, align 8, !dbg !590
  %54 = load i32, i32* %x, align 4, !dbg !591
  %idxprom81 = zext i32 %54 to i64, !dbg !592
  %arrayidx82 = getelementptr inbounds [5 x i64], [5 x i64]* %D, i64 0, i64 %idxprom81, !dbg !592
  %55 = load i64, i64* %arrayidx82, align 8, !dbg !592
  %56 = load i32, i32* %x, align 4, !dbg !593
  %add83 = add i32 %56, 20, !dbg !594
  %idxprom84 = zext i32 %add83 to i64, !dbg !595
  %57 = load i64*, i64** %A.addr, align 8, !dbg !595
  %arrayidx85 = getelementptr inbounds i64, i64* %57, i64 %idxprom84, !dbg !595
  %58 = load i64, i64* %arrayidx85, align 8, !dbg !596
  %xor86 = xor i64 %58, %55, !dbg !596
  store i64 %xor86, i64* %arrayidx85, align 8, !dbg !596
  br label %for.inc87, !dbg !597

for.inc87:                                        ; preds = %for.body57
  %59 = load i32, i32* %x, align 4, !dbg !598
  %inc88 = add i32 %59, 1, !dbg !598
  store i32 %inc88, i32* %x, align 4, !dbg !598
  br label %for.cond55, !dbg !600

for.end89:                                        ; preds = %for.cond55
  ret void, !dbg !601
}

; Function Attrs: nounwind uwtable
define internal void @keccak_pi(i64* %A) #0 !dbg !59 {
entry:
  %A.addr = alloca i64*, align 8
  %A1 = alloca i64, align 8
  store i64* %A, i64** %A.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %A.addr, metadata !602, metadata !67), !dbg !603
  call void @llvm.dbg.declare(metadata i64* %A1, metadata !604, metadata !67), !dbg !605
  %0 = load i64*, i64** %A.addr, align 8, !dbg !606
  %arrayidx = getelementptr inbounds i64, i64* %0, i64 1, !dbg !606
  %1 = load i64, i64* %arrayidx, align 8, !dbg !606
  store i64 %1, i64* %A1, align 8, !dbg !607
  %2 = load i64*, i64** %A.addr, align 8, !dbg !608
  %arrayidx1 = getelementptr inbounds i64, i64* %2, i64 6, !dbg !608
  %3 = load i64, i64* %arrayidx1, align 8, !dbg !608
  %4 = load i64*, i64** %A.addr, align 8, !dbg !609
  %arrayidx2 = getelementptr inbounds i64, i64* %4, i64 1, !dbg !609
  store i64 %3, i64* %arrayidx2, align 8, !dbg !610
  %5 = load i64*, i64** %A.addr, align 8, !dbg !611
  %arrayidx3 = getelementptr inbounds i64, i64* %5, i64 9, !dbg !611
  %6 = load i64, i64* %arrayidx3, align 8, !dbg !611
  %7 = load i64*, i64** %A.addr, align 8, !dbg !612
  %arrayidx4 = getelementptr inbounds i64, i64* %7, i64 6, !dbg !612
  store i64 %6, i64* %arrayidx4, align 8, !dbg !613
  %8 = load i64*, i64** %A.addr, align 8, !dbg !614
  %arrayidx5 = getelementptr inbounds i64, i64* %8, i64 22, !dbg !614
  %9 = load i64, i64* %arrayidx5, align 8, !dbg !614
  %10 = load i64*, i64** %A.addr, align 8, !dbg !615
  %arrayidx6 = getelementptr inbounds i64, i64* %10, i64 9, !dbg !615
  store i64 %9, i64* %arrayidx6, align 8, !dbg !616
  %11 = load i64*, i64** %A.addr, align 8, !dbg !617
  %arrayidx7 = getelementptr inbounds i64, i64* %11, i64 14, !dbg !617
  %12 = load i64, i64* %arrayidx7, align 8, !dbg !617
  %13 = load i64*, i64** %A.addr, align 8, !dbg !618
  %arrayidx8 = getelementptr inbounds i64, i64* %13, i64 22, !dbg !618
  store i64 %12, i64* %arrayidx8, align 8, !dbg !619
  %14 = load i64*, i64** %A.addr, align 8, !dbg !620
  %arrayidx9 = getelementptr inbounds i64, i64* %14, i64 20, !dbg !620
  %15 = load i64, i64* %arrayidx9, align 8, !dbg !620
  %16 = load i64*, i64** %A.addr, align 8, !dbg !621
  %arrayidx10 = getelementptr inbounds i64, i64* %16, i64 14, !dbg !621
  store i64 %15, i64* %arrayidx10, align 8, !dbg !622
  %17 = load i64*, i64** %A.addr, align 8, !dbg !623
  %arrayidx11 = getelementptr inbounds i64, i64* %17, i64 2, !dbg !623
  %18 = load i64, i64* %arrayidx11, align 8, !dbg !623
  %19 = load i64*, i64** %A.addr, align 8, !dbg !624
  %arrayidx12 = getelementptr inbounds i64, i64* %19, i64 20, !dbg !624
  store i64 %18, i64* %arrayidx12, align 8, !dbg !625
  %20 = load i64*, i64** %A.addr, align 8, !dbg !626
  %arrayidx13 = getelementptr inbounds i64, i64* %20, i64 12, !dbg !626
  %21 = load i64, i64* %arrayidx13, align 8, !dbg !626
  %22 = load i64*, i64** %A.addr, align 8, !dbg !627
  %arrayidx14 = getelementptr inbounds i64, i64* %22, i64 2, !dbg !627
  store i64 %21, i64* %arrayidx14, align 8, !dbg !628
  %23 = load i64*, i64** %A.addr, align 8, !dbg !629
  %arrayidx15 = getelementptr inbounds i64, i64* %23, i64 13, !dbg !629
  %24 = load i64, i64* %arrayidx15, align 8, !dbg !629
  %25 = load i64*, i64** %A.addr, align 8, !dbg !630
  %arrayidx16 = getelementptr inbounds i64, i64* %25, i64 12, !dbg !630
  store i64 %24, i64* %arrayidx16, align 8, !dbg !631
  %26 = load i64*, i64** %A.addr, align 8, !dbg !632
  %arrayidx17 = getelementptr inbounds i64, i64* %26, i64 19, !dbg !632
  %27 = load i64, i64* %arrayidx17, align 8, !dbg !632
  %28 = load i64*, i64** %A.addr, align 8, !dbg !633
  %arrayidx18 = getelementptr inbounds i64, i64* %28, i64 13, !dbg !633
  store i64 %27, i64* %arrayidx18, align 8, !dbg !634
  %29 = load i64*, i64** %A.addr, align 8, !dbg !635
  %arrayidx19 = getelementptr inbounds i64, i64* %29, i64 23, !dbg !635
  %30 = load i64, i64* %arrayidx19, align 8, !dbg !635
  %31 = load i64*, i64** %A.addr, align 8, !dbg !636
  %arrayidx20 = getelementptr inbounds i64, i64* %31, i64 19, !dbg !636
  store i64 %30, i64* %arrayidx20, align 8, !dbg !637
  %32 = load i64*, i64** %A.addr, align 8, !dbg !638
  %arrayidx21 = getelementptr inbounds i64, i64* %32, i64 15, !dbg !638
  %33 = load i64, i64* %arrayidx21, align 8, !dbg !638
  %34 = load i64*, i64** %A.addr, align 8, !dbg !639
  %arrayidx22 = getelementptr inbounds i64, i64* %34, i64 23, !dbg !639
  store i64 %33, i64* %arrayidx22, align 8, !dbg !640
  %35 = load i64*, i64** %A.addr, align 8, !dbg !641
  %arrayidx23 = getelementptr inbounds i64, i64* %35, i64 4, !dbg !641
  %36 = load i64, i64* %arrayidx23, align 8, !dbg !641
  %37 = load i64*, i64** %A.addr, align 8, !dbg !642
  %arrayidx24 = getelementptr inbounds i64, i64* %37, i64 15, !dbg !642
  store i64 %36, i64* %arrayidx24, align 8, !dbg !643
  %38 = load i64*, i64** %A.addr, align 8, !dbg !644
  %arrayidx25 = getelementptr inbounds i64, i64* %38, i64 24, !dbg !644
  %39 = load i64, i64* %arrayidx25, align 8, !dbg !644
  %40 = load i64*, i64** %A.addr, align 8, !dbg !645
  %arrayidx26 = getelementptr inbounds i64, i64* %40, i64 4, !dbg !645
  store i64 %39, i64* %arrayidx26, align 8, !dbg !646
  %41 = load i64*, i64** %A.addr, align 8, !dbg !647
  %arrayidx27 = getelementptr inbounds i64, i64* %41, i64 21, !dbg !647
  %42 = load i64, i64* %arrayidx27, align 8, !dbg !647
  %43 = load i64*, i64** %A.addr, align 8, !dbg !648
  %arrayidx28 = getelementptr inbounds i64, i64* %43, i64 24, !dbg !648
  store i64 %42, i64* %arrayidx28, align 8, !dbg !649
  %44 = load i64*, i64** %A.addr, align 8, !dbg !650
  %arrayidx29 = getelementptr inbounds i64, i64* %44, i64 8, !dbg !650
  %45 = load i64, i64* %arrayidx29, align 8, !dbg !650
  %46 = load i64*, i64** %A.addr, align 8, !dbg !651
  %arrayidx30 = getelementptr inbounds i64, i64* %46, i64 21, !dbg !651
  store i64 %45, i64* %arrayidx30, align 8, !dbg !652
  %47 = load i64*, i64** %A.addr, align 8, !dbg !653
  %arrayidx31 = getelementptr inbounds i64, i64* %47, i64 16, !dbg !653
  %48 = load i64, i64* %arrayidx31, align 8, !dbg !653
  %49 = load i64*, i64** %A.addr, align 8, !dbg !654
  %arrayidx32 = getelementptr inbounds i64, i64* %49, i64 8, !dbg !654
  store i64 %48, i64* %arrayidx32, align 8, !dbg !655
  %50 = load i64*, i64** %A.addr, align 8, !dbg !656
  %arrayidx33 = getelementptr inbounds i64, i64* %50, i64 5, !dbg !656
  %51 = load i64, i64* %arrayidx33, align 8, !dbg !656
  %52 = load i64*, i64** %A.addr, align 8, !dbg !657
  %arrayidx34 = getelementptr inbounds i64, i64* %52, i64 16, !dbg !657
  store i64 %51, i64* %arrayidx34, align 8, !dbg !658
  %53 = load i64*, i64** %A.addr, align 8, !dbg !659
  %arrayidx35 = getelementptr inbounds i64, i64* %53, i64 3, !dbg !659
  %54 = load i64, i64* %arrayidx35, align 8, !dbg !659
  %55 = load i64*, i64** %A.addr, align 8, !dbg !660
  %arrayidx36 = getelementptr inbounds i64, i64* %55, i64 5, !dbg !660
  store i64 %54, i64* %arrayidx36, align 8, !dbg !661
  %56 = load i64*, i64** %A.addr, align 8, !dbg !662
  %arrayidx37 = getelementptr inbounds i64, i64* %56, i64 18, !dbg !662
  %57 = load i64, i64* %arrayidx37, align 8, !dbg !662
  %58 = load i64*, i64** %A.addr, align 8, !dbg !663
  %arrayidx38 = getelementptr inbounds i64, i64* %58, i64 3, !dbg !663
  store i64 %57, i64* %arrayidx38, align 8, !dbg !664
  %59 = load i64*, i64** %A.addr, align 8, !dbg !665
  %arrayidx39 = getelementptr inbounds i64, i64* %59, i64 17, !dbg !665
  %60 = load i64, i64* %arrayidx39, align 8, !dbg !665
  %61 = load i64*, i64** %A.addr, align 8, !dbg !666
  %arrayidx40 = getelementptr inbounds i64, i64* %61, i64 18, !dbg !666
  store i64 %60, i64* %arrayidx40, align 8, !dbg !667
  %62 = load i64*, i64** %A.addr, align 8, !dbg !668
  %arrayidx41 = getelementptr inbounds i64, i64* %62, i64 11, !dbg !668
  %63 = load i64, i64* %arrayidx41, align 8, !dbg !668
  %64 = load i64*, i64** %A.addr, align 8, !dbg !669
  %arrayidx42 = getelementptr inbounds i64, i64* %64, i64 17, !dbg !669
  store i64 %63, i64* %arrayidx42, align 8, !dbg !670
  %65 = load i64*, i64** %A.addr, align 8, !dbg !671
  %arrayidx43 = getelementptr inbounds i64, i64* %65, i64 7, !dbg !671
  %66 = load i64, i64* %arrayidx43, align 8, !dbg !671
  %67 = load i64*, i64** %A.addr, align 8, !dbg !672
  %arrayidx44 = getelementptr inbounds i64, i64* %67, i64 11, !dbg !672
  store i64 %66, i64* %arrayidx44, align 8, !dbg !673
  %68 = load i64*, i64** %A.addr, align 8, !dbg !674
  %arrayidx45 = getelementptr inbounds i64, i64* %68, i64 10, !dbg !674
  %69 = load i64, i64* %arrayidx45, align 8, !dbg !674
  %70 = load i64*, i64** %A.addr, align 8, !dbg !675
  %arrayidx46 = getelementptr inbounds i64, i64* %70, i64 7, !dbg !675
  store i64 %69, i64* %arrayidx46, align 8, !dbg !676
  %71 = load i64, i64* %A1, align 8, !dbg !677
  %72 = load i64*, i64** %A.addr, align 8, !dbg !678
  %arrayidx47 = getelementptr inbounds i64, i64* %72, i64 10, !dbg !678
  store i64 %71, i64* %arrayidx47, align 8, !dbg !679
  ret void, !dbg !680
}

; Function Attrs: nounwind uwtable
define internal void @keccak_chi(i64* %A) #0 !dbg !60 {
entry:
  %A.addr = alloca i64*, align 8
  %i = alloca i32, align 4
  %A0 = alloca i64, align 8
  %A1 = alloca i64, align 8
  store i64* %A, i64** %A.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %A.addr, metadata !681, metadata !67), !dbg !682
  call void @llvm.dbg.declare(metadata i32* %i, metadata !683, metadata !67), !dbg !684
  store i32 0, i32* %i, align 4, !dbg !685
  br label %for.cond, !dbg !687

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !688
  %cmp = icmp slt i32 %0, 25, !dbg !691
  br i1 %cmp, label %for.body, label %for.end, !dbg !692

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i64* %A0, metadata !693, metadata !67), !dbg !695
  %1 = load i32, i32* %i, align 4, !dbg !696
  %add = add nsw i32 0, %1, !dbg !697
  %idxprom = sext i32 %add to i64, !dbg !698
  %2 = load i64*, i64** %A.addr, align 8, !dbg !698
  %arrayidx = getelementptr inbounds i64, i64* %2, i64 %idxprom, !dbg !698
  %3 = load i64, i64* %arrayidx, align 8, !dbg !698
  store i64 %3, i64* %A0, align 8, !dbg !695
  call void @llvm.dbg.declare(metadata i64* %A1, metadata !699, metadata !67), !dbg !700
  %4 = load i32, i32* %i, align 4, !dbg !701
  %add1 = add nsw i32 1, %4, !dbg !702
  %idxprom2 = sext i32 %add1 to i64, !dbg !703
  %5 = load i64*, i64** %A.addr, align 8, !dbg !703
  %arrayidx3 = getelementptr inbounds i64, i64* %5, i64 %idxprom2, !dbg !703
  %6 = load i64, i64* %arrayidx3, align 8, !dbg !703
  store i64 %6, i64* %A1, align 8, !dbg !700
  %7 = load i64, i64* %A1, align 8, !dbg !704
  %neg = xor i64 %7, -1, !dbg !705
  %8 = load i32, i32* %i, align 4, !dbg !706
  %add4 = add nsw i32 2, %8, !dbg !707
  %idxprom5 = sext i32 %add4 to i64, !dbg !708
  %9 = load i64*, i64** %A.addr, align 8, !dbg !708
  %arrayidx6 = getelementptr inbounds i64, i64* %9, i64 %idxprom5, !dbg !708
  %10 = load i64, i64* %arrayidx6, align 8, !dbg !708
  %and = and i64 %neg, %10, !dbg !709
  %11 = load i32, i32* %i, align 4, !dbg !710
  %add7 = add nsw i32 0, %11, !dbg !711
  %idxprom8 = sext i32 %add7 to i64, !dbg !712
  %12 = load i64*, i64** %A.addr, align 8, !dbg !712
  %arrayidx9 = getelementptr inbounds i64, i64* %12, i64 %idxprom8, !dbg !712
  %13 = load i64, i64* %arrayidx9, align 8, !dbg !713
  %xor = xor i64 %13, %and, !dbg !713
  store i64 %xor, i64* %arrayidx9, align 8, !dbg !713
  %14 = load i32, i32* %i, align 4, !dbg !714
  %add10 = add nsw i32 2, %14, !dbg !715
  %idxprom11 = sext i32 %add10 to i64, !dbg !716
  %15 = load i64*, i64** %A.addr, align 8, !dbg !716
  %arrayidx12 = getelementptr inbounds i64, i64* %15, i64 %idxprom11, !dbg !716
  %16 = load i64, i64* %arrayidx12, align 8, !dbg !716
  %neg13 = xor i64 %16, -1, !dbg !717
  %17 = load i32, i32* %i, align 4, !dbg !718
  %add14 = add nsw i32 3, %17, !dbg !719
  %idxprom15 = sext i32 %add14 to i64, !dbg !720
  %18 = load i64*, i64** %A.addr, align 8, !dbg !720
  %arrayidx16 = getelementptr inbounds i64, i64* %18, i64 %idxprom15, !dbg !720
  %19 = load i64, i64* %arrayidx16, align 8, !dbg !720
  %and17 = and i64 %neg13, %19, !dbg !721
  %20 = load i32, i32* %i, align 4, !dbg !722
  %add18 = add nsw i32 1, %20, !dbg !723
  %idxprom19 = sext i32 %add18 to i64, !dbg !724
  %21 = load i64*, i64** %A.addr, align 8, !dbg !724
  %arrayidx20 = getelementptr inbounds i64, i64* %21, i64 %idxprom19, !dbg !724
  %22 = load i64, i64* %arrayidx20, align 8, !dbg !725
  %xor21 = xor i64 %22, %and17, !dbg !725
  store i64 %xor21, i64* %arrayidx20, align 8, !dbg !725
  %23 = load i32, i32* %i, align 4, !dbg !726
  %add22 = add nsw i32 3, %23, !dbg !727
  %idxprom23 = sext i32 %add22 to i64, !dbg !728
  %24 = load i64*, i64** %A.addr, align 8, !dbg !728
  %arrayidx24 = getelementptr inbounds i64, i64* %24, i64 %idxprom23, !dbg !728
  %25 = load i64, i64* %arrayidx24, align 8, !dbg !728
  %neg25 = xor i64 %25, -1, !dbg !729
  %26 = load i32, i32* %i, align 4, !dbg !730
  %add26 = add nsw i32 4, %26, !dbg !731
  %idxprom27 = sext i32 %add26 to i64, !dbg !732
  %27 = load i64*, i64** %A.addr, align 8, !dbg !732
  %arrayidx28 = getelementptr inbounds i64, i64* %27, i64 %idxprom27, !dbg !732
  %28 = load i64, i64* %arrayidx28, align 8, !dbg !732
  %and29 = and i64 %neg25, %28, !dbg !733
  %29 = load i32, i32* %i, align 4, !dbg !734
  %add30 = add nsw i32 2, %29, !dbg !735
  %idxprom31 = sext i32 %add30 to i64, !dbg !736
  %30 = load i64*, i64** %A.addr, align 8, !dbg !736
  %arrayidx32 = getelementptr inbounds i64, i64* %30, i64 %idxprom31, !dbg !736
  %31 = load i64, i64* %arrayidx32, align 8, !dbg !737
  %xor33 = xor i64 %31, %and29, !dbg !737
  store i64 %xor33, i64* %arrayidx32, align 8, !dbg !737
  %32 = load i32, i32* %i, align 4, !dbg !738
  %add34 = add nsw i32 4, %32, !dbg !739
  %idxprom35 = sext i32 %add34 to i64, !dbg !740
  %33 = load i64*, i64** %A.addr, align 8, !dbg !740
  %arrayidx36 = getelementptr inbounds i64, i64* %33, i64 %idxprom35, !dbg !740
  %34 = load i64, i64* %arrayidx36, align 8, !dbg !740
  %neg37 = xor i64 %34, -1, !dbg !741
  %35 = load i64, i64* %A0, align 8, !dbg !742
  %and38 = and i64 %neg37, %35, !dbg !743
  %36 = load i32, i32* %i, align 4, !dbg !744
  %add39 = add nsw i32 3, %36, !dbg !745
  %idxprom40 = sext i32 %add39 to i64, !dbg !746
  %37 = load i64*, i64** %A.addr, align 8, !dbg !746
  %arrayidx41 = getelementptr inbounds i64, i64* %37, i64 %idxprom40, !dbg !746
  %38 = load i64, i64* %arrayidx41, align 8, !dbg !747
  %xor42 = xor i64 %38, %and38, !dbg !747
  store i64 %xor42, i64* %arrayidx41, align 8, !dbg !747
  %39 = load i64, i64* %A0, align 8, !dbg !748
  %neg43 = xor i64 %39, -1, !dbg !749
  %40 = load i64, i64* %A1, align 8, !dbg !750
  %and44 = and i64 %neg43, %40, !dbg !751
  %41 = load i32, i32* %i, align 4, !dbg !752
  %add45 = add nsw i32 4, %41, !dbg !753
  %idxprom46 = sext i32 %add45 to i64, !dbg !754
  %42 = load i64*, i64** %A.addr, align 8, !dbg !754
  %arrayidx47 = getelementptr inbounds i64, i64* %42, i64 %idxprom46, !dbg !754
  %43 = load i64, i64* %arrayidx47, align 8, !dbg !755
  %xor48 = xor i64 %43, %and44, !dbg !755
  store i64 %xor48, i64* %arrayidx47, align 8, !dbg !755
  br label %for.inc, !dbg !756

for.inc:                                          ; preds = %for.body
  %44 = load i32, i32* %i, align 4, !dbg !757
  %add49 = add nsw i32 %44, 5, !dbg !757
  store i32 %add49, i32* %i, align 4, !dbg !757
  br label %for.cond, !dbg !759

for.end:                                          ; preds = %for.cond
  ret void, !dbg !760
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { argmemonly nounwind }
attributes #3 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!63, !64}
!llvm.ident = !{!65}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !15, globals: !61)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/sha3.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!2 = !{}
!3 = !{!4, !7, !8, !10, !12}
!4 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !5, line: 62, baseType: !6)
!5 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!6 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!7 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !9)
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64, align: 64)
!13 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !14, line: 55, baseType: !6)
!14 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!15 = !{!16, !34, !35, !36, !37, !43, !47, !50, !55, !58, !59, !60}
!16 = distinct !DISubprogram(name: "rhash_sha3_224_init", scope: !1, file: !1, line: 54, type: !17, isLocal: false, isDefinition: true, scopeLine: 55, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!17 = !DISubroutineType(types: !18)
!18 = !{null, !19}
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "sha3_ctx", file: !21, line: 30, baseType: !22)
!21 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/sha3.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!22 = !DICompositeType(tag: DW_TAG_structure_type, name: "sha3_ctx", file: !21, line: 20, size: 3200, align: 64, elements: !23)
!23 = !{!24, !28, !32, !33}
!24 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !22, file: !21, line: 23, baseType: !25, size: 1600, align: 64)
!25 = !DICompositeType(tag: DW_TAG_array_type, baseType: !13, size: 1600, align: 64, elements: !26)
!26 = !{!27}
!27 = !DISubrange(count: 25)
!28 = !DIDerivedType(tag: DW_TAG_member, name: "message", scope: !22, file: !21, line: 25, baseType: !29, size: 1536, align: 64, offset: 1600)
!29 = !DICompositeType(tag: DW_TAG_array_type, baseType: !13, size: 1536, align: 64, elements: !30)
!30 = !{!31}
!31 = !DISubrange(count: 24)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "rest", scope: !22, file: !21, line: 27, baseType: !7, size: 32, align: 32, offset: 3136)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "block_size", scope: !22, file: !21, line: 29, baseType: !7, size: 32, align: 32, offset: 3168)
!34 = distinct !DISubprogram(name: "rhash_sha3_256_init", scope: !1, file: !1, line: 64, type: !17, isLocal: false, isDefinition: true, scopeLine: 65, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!35 = distinct !DISubprogram(name: "rhash_sha3_384_init", scope: !1, file: !1, line: 74, type: !17, isLocal: false, isDefinition: true, scopeLine: 75, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!36 = distinct !DISubprogram(name: "rhash_sha3_512_init", scope: !1, file: !1, line: 84, type: !17, isLocal: false, isDefinition: true, scopeLine: 85, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!37 = distinct !DISubprogram(name: "rhash_sha3_update", scope: !1, file: !1, line: 263, type: !38, isLocal: false, isDefinition: true, scopeLine: 264, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!38 = !DISubroutineType(types: !39)
!39 = !{null, !19, !40, !4}
!40 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!41 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !42)
!42 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!43 = distinct !DISubprogram(name: "rhash_sha3_final", scope: !1, file: !1, line: 308, type: !44, isLocal: false, isDefinition: true, scopeLine: 309, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!44 = !DISubroutineType(types: !45)
!45 = !{null, !19, !46}
!46 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!47 = distinct !DISubprogram(name: "rhash_keccak_init", scope: !1, file: !1, line: 39, type: !48, isLocal: true, isDefinition: true, scopeLine: 40, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!48 = !DISubroutineType(types: !49)
!49 = !{null, !19, !7}
!50 = distinct !DISubprogram(name: "rhash_sha3_process_block", scope: !1, file: !1, line: 207, type: !51, isLocal: true, isDefinition: true, scopeLine: 208, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!51 = !DISubroutineType(types: !52)
!52 = !{null, !12, !53, !4}
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!54 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !13)
!55 = distinct !DISubprogram(name: "rhash_sha3_permutation", scope: !1, file: !1, line: 159, type: !56, isLocal: true, isDefinition: true, scopeLine: 160, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!56 = !DISubroutineType(types: !57)
!57 = !{null, !12}
!58 = distinct !DISubprogram(name: "keccak_theta", scope: !1, file: !1, line: 90, type: !56, isLocal: true, isDefinition: true, scopeLine: 91, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!59 = distinct !DISubprogram(name: "keccak_pi", scope: !1, file: !1, line: 114, type: !56, isLocal: true, isDefinition: true, scopeLine: 115, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!60 = distinct !DISubprogram(name: "keccak_chi", scope: !1, file: !1, line: 146, type: !56, isLocal: true, isDefinition: true, scopeLine: 147, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!61 = !{!62}
!62 = !DIGlobalVariable(name: "keccak_round_constants", scope: !0, file: !1, line: 29, type: !29, isLocal: true, isDefinition: true, variable: [24 x i64]* @keccak_round_constants)
!63 = !{i32 2, !"Dwarf Version", i32 4}
!64 = !{i32 2, !"Debug Info Version", i32 3}
!65 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!66 = !DILocalVariable(name: "ctx", arg: 1, scope: !16, file: !1, line: 54, type: !19)
!67 = !DIExpression()
!68 = !DILocation(line: 54, column: 36, scope: !16)
!69 = !DILocation(line: 56, column: 20, scope: !16)
!70 = !DILocation(line: 56, column: 2, scope: !16)
!71 = !DILocation(line: 57, column: 1, scope: !16)
!72 = !DILocalVariable(name: "ctx", arg: 1, scope: !47, file: !1, line: 39, type: !19)
!73 = !DILocation(line: 39, column: 41, scope: !47)
!74 = !DILocalVariable(name: "bits", arg: 2, scope: !47, file: !1, line: 39, type: !7)
!75 = !DILocation(line: 39, column: 55, scope: !47)
!76 = !DILocalVariable(name: "rate", scope: !47, file: !1, line: 42, type: !7)
!77 = !DILocation(line: 42, column: 11, scope: !47)
!78 = !DILocation(line: 42, column: 25, scope: !47)
!79 = !DILocation(line: 42, column: 30, scope: !47)
!80 = !DILocation(line: 42, column: 23, scope: !47)
!81 = !DILocation(line: 44, column: 9, scope: !47)
!82 = !DILocation(line: 44, column: 2, scope: !47)
!83 = !DILocation(line: 45, column: 20, scope: !47)
!84 = !DILocation(line: 45, column: 25, scope: !47)
!85 = !DILocation(line: 45, column: 2, scope: !47)
!86 = !DILocation(line: 45, column: 7, scope: !47)
!87 = !DILocation(line: 45, column: 18, scope: !47)
!88 = !DILocation(line: 46, column: 2, scope: !47)
!89 = !DILocation(line: 46, column: 2, scope: !90)
!90 = !DILexicalBlockFile(scope: !47, file: !1, discriminator: 1)
!91 = !DILocation(line: 46, column: 2, scope: !92)
!92 = !DILexicalBlockFile(scope: !47, file: !1, discriminator: 2)
!93 = !DILocation(line: 46, column: 2, scope: !94)
!94 = !DILexicalBlockFile(scope: !47, file: !1, discriminator: 3)
!95 = !DILocation(line: 46, column: 2, scope: !96)
!96 = !DILexicalBlockFile(scope: !47, file: !1, discriminator: 4)
!97 = !DILocation(line: 47, column: 1, scope: !47)
!98 = !DILocalVariable(name: "ctx", arg: 1, scope: !34, file: !1, line: 64, type: !19)
!99 = !DILocation(line: 64, column: 36, scope: !34)
!100 = !DILocation(line: 66, column: 20, scope: !34)
!101 = !DILocation(line: 66, column: 2, scope: !34)
!102 = !DILocation(line: 67, column: 1, scope: !34)
!103 = !DILocalVariable(name: "ctx", arg: 1, scope: !35, file: !1, line: 74, type: !19)
!104 = !DILocation(line: 74, column: 36, scope: !35)
!105 = !DILocation(line: 76, column: 20, scope: !35)
!106 = !DILocation(line: 76, column: 2, scope: !35)
!107 = !DILocation(line: 77, column: 1, scope: !35)
!108 = !DILocalVariable(name: "ctx", arg: 1, scope: !36, file: !1, line: 84, type: !19)
!109 = !DILocation(line: 84, column: 36, scope: !36)
!110 = !DILocation(line: 86, column: 20, scope: !36)
!111 = !DILocation(line: 86, column: 2, scope: !36)
!112 = !DILocation(line: 87, column: 1, scope: !36)
!113 = !DILocalVariable(name: "ctx", arg: 1, scope: !37, file: !1, line: 263, type: !19)
!114 = !DILocation(line: 263, column: 34, scope: !37)
!115 = !DILocalVariable(name: "msg", arg: 2, scope: !37, file: !1, line: 263, type: !40)
!116 = !DILocation(line: 263, column: 60, scope: !37)
!117 = !DILocalVariable(name: "size", arg: 3, scope: !37, file: !1, line: 263, type: !4)
!118 = !DILocation(line: 263, column: 72, scope: !37)
!119 = !DILocalVariable(name: "index", scope: !37, file: !1, line: 265, type: !4)
!120 = !DILocation(line: 265, column: 9, scope: !37)
!121 = !DILocation(line: 265, column: 25, scope: !37)
!122 = !DILocation(line: 265, column: 30, scope: !37)
!123 = !DILocation(line: 265, column: 17, scope: !37)
!124 = !DILocalVariable(name: "block_size", scope: !37, file: !1, line: 266, type: !4)
!125 = !DILocation(line: 266, column: 9, scope: !37)
!126 = !DILocation(line: 266, column: 30, scope: !37)
!127 = !DILocation(line: 266, column: 35, scope: !37)
!128 = !DILocation(line: 266, column: 22, scope: !37)
!129 = !DILocation(line: 268, column: 6, scope: !130)
!130 = distinct !DILexicalBlock(scope: !37, file: !1, line: 268, column: 6)
!131 = !DILocation(line: 268, column: 11, scope: !130)
!132 = !DILocation(line: 268, column: 16, scope: !130)
!133 = !DILocation(line: 268, column: 6, scope: !37)
!134 = !DILocation(line: 268, column: 34, scope: !135)
!135 = !DILexicalBlockFile(scope: !130, file: !1, discriminator: 1)
!136 = !DILocation(line: 269, column: 26, scope: !37)
!137 = !DILocation(line: 269, column: 31, scope: !37)
!138 = !DILocation(line: 269, column: 38, scope: !37)
!139 = !DILocation(line: 269, column: 36, scope: !37)
!140 = !DILocation(line: 269, column: 46, scope: !37)
!141 = !DILocation(line: 269, column: 44, scope: !37)
!142 = !DILocation(line: 269, column: 14, scope: !37)
!143 = !DILocation(line: 269, column: 2, scope: !37)
!144 = !DILocation(line: 269, column: 7, scope: !37)
!145 = !DILocation(line: 269, column: 12, scope: !37)
!146 = !DILocation(line: 272, column: 6, scope: !147)
!147 = distinct !DILexicalBlock(scope: !37, file: !1, line: 272, column: 6)
!148 = !DILocation(line: 272, column: 6, scope: !37)
!149 = !DILocalVariable(name: "left", scope: !150, file: !1, line: 273, type: !4)
!150 = distinct !DILexicalBlock(scope: !147, file: !1, line: 272, column: 13)
!151 = !DILocation(line: 273, column: 10, scope: !150)
!152 = !DILocation(line: 273, column: 17, scope: !150)
!153 = !DILocation(line: 273, column: 30, scope: !150)
!154 = !DILocation(line: 273, column: 28, scope: !150)
!155 = !DILocation(line: 274, column: 17, scope: !150)
!156 = !DILocation(line: 274, column: 22, scope: !150)
!157 = !DILocation(line: 274, column: 10, scope: !150)
!158 = !DILocation(line: 274, column: 32, scope: !150)
!159 = !DILocation(line: 274, column: 30, scope: !150)
!160 = !DILocation(line: 274, column: 39, scope: !150)
!161 = !DILocation(line: 274, column: 45, scope: !150)
!162 = !DILocation(line: 274, column: 52, scope: !150)
!163 = !DILocation(line: 274, column: 50, scope: !150)
!164 = !DILocation(line: 274, column: 59, scope: !165)
!165 = !DILexicalBlockFile(scope: !150, file: !1, discriminator: 1)
!166 = !DILocation(line: 274, column: 45, scope: !165)
!167 = !DILocation(line: 274, column: 66, scope: !168)
!168 = !DILexicalBlockFile(scope: !150, file: !1, discriminator: 2)
!169 = !DILocation(line: 274, column: 45, scope: !168)
!170 = !DILocation(line: 274, column: 45, scope: !171)
!171 = !DILexicalBlockFile(scope: !150, file: !1, discriminator: 3)
!172 = !DILocation(line: 274, column: 3, scope: !171)
!173 = !DILocation(line: 275, column: 7, scope: !174)
!174 = distinct !DILexicalBlock(scope: !150, file: !1, line: 275, column: 7)
!175 = !DILocation(line: 275, column: 14, scope: !174)
!176 = !DILocation(line: 275, column: 12, scope: !174)
!177 = !DILocation(line: 275, column: 7, scope: !150)
!178 = !DILocation(line: 275, column: 20, scope: !179)
!179 = !DILexicalBlockFile(scope: !174, file: !1, discriminator: 1)
!180 = !DILocation(line: 278, column: 28, scope: !150)
!181 = !DILocation(line: 278, column: 33, scope: !150)
!182 = !DILocation(line: 278, column: 39, scope: !150)
!183 = !DILocation(line: 278, column: 44, scope: !150)
!184 = !DILocation(line: 278, column: 53, scope: !150)
!185 = !DILocation(line: 278, column: 3, scope: !150)
!186 = !DILocation(line: 279, column: 11, scope: !150)
!187 = !DILocation(line: 279, column: 8, scope: !150)
!188 = !DILocation(line: 280, column: 11, scope: !150)
!189 = !DILocation(line: 280, column: 8, scope: !150)
!190 = !DILocation(line: 281, column: 2, scope: !150)
!191 = !DILocation(line: 282, column: 2, scope: !37)
!192 = !DILocation(line: 282, column: 9, scope: !193)
!193 = !DILexicalBlockFile(scope: !37, file: !1, discriminator: 1)
!194 = !DILocation(line: 282, column: 17, scope: !193)
!195 = !DILocation(line: 282, column: 14, scope: !193)
!196 = !DILocation(line: 282, column: 2, scope: !193)
!197 = !DILocalVariable(name: "aligned_message_block", scope: !198, file: !1, line: 283, type: !12)
!198 = distinct !DILexicalBlock(scope: !37, file: !1, line: 282, column: 29)
!199 = !DILocation(line: 283, column: 13, scope: !198)
!200 = !DILocation(line: 284, column: 7, scope: !201)
!201 = distinct !DILexicalBlock(scope: !198, file: !1, line: 284, column: 7)
!202 = !DILocation(line: 284, column: 7, scope: !198)
!203 = !DILocation(line: 287, column: 39, scope: !204)
!204 = distinct !DILexicalBlock(scope: !201, file: !1, line: 284, column: 27)
!205 = !DILocation(line: 287, column: 28, scope: !204)
!206 = !DILocation(line: 287, column: 26, scope: !204)
!207 = !DILocation(line: 288, column: 3, scope: !204)
!208 = !DILocation(line: 289, column: 11, scope: !209)
!209 = distinct !DILexicalBlock(scope: !201, file: !1, line: 288, column: 10)
!210 = !DILocation(line: 289, column: 16, scope: !209)
!211 = !DILocation(line: 289, column: 4, scope: !209)
!212 = !DILocation(line: 289, column: 25, scope: !209)
!213 = !DILocation(line: 289, column: 30, scope: !209)
!214 = !DILocation(line: 290, column: 28, scope: !209)
!215 = !DILocation(line: 290, column: 33, scope: !209)
!216 = !DILocation(line: 290, column: 26, scope: !209)
!217 = !DILocation(line: 293, column: 28, scope: !198)
!218 = !DILocation(line: 293, column: 33, scope: !198)
!219 = !DILocation(line: 293, column: 39, scope: !198)
!220 = !DILocation(line: 293, column: 62, scope: !198)
!221 = !DILocation(line: 293, column: 3, scope: !198)
!222 = !DILocation(line: 294, column: 11, scope: !198)
!223 = !DILocation(line: 294, column: 8, scope: !198)
!224 = !DILocation(line: 295, column: 11, scope: !198)
!225 = !DILocation(line: 295, column: 8, scope: !198)
!226 = !DILocation(line: 282, column: 2, scope: !227)
!227 = !DILexicalBlockFile(scope: !37, file: !1, discriminator: 2)
!228 = !DILocation(line: 297, column: 6, scope: !229)
!229 = distinct !DILexicalBlock(scope: !37, file: !1, line: 297, column: 6)
!230 = !DILocation(line: 297, column: 6, scope: !37)
!231 = !DILocation(line: 298, column: 10, scope: !232)
!232 = distinct !DILexicalBlock(scope: !229, file: !1, line: 297, column: 12)
!233 = !DILocation(line: 298, column: 15, scope: !232)
!234 = !DILocation(line: 298, column: 3, scope: !232)
!235 = !DILocation(line: 298, column: 24, scope: !232)
!236 = !DILocation(line: 298, column: 29, scope: !232)
!237 = !DILocation(line: 299, column: 2, scope: !232)
!238 = !DILocation(line: 300, column: 1, scope: !37)
!239 = !DILocalVariable(name: "hash", arg: 1, scope: !50, file: !1, line: 207, type: !12)
!240 = !DILocation(line: 207, column: 47, scope: !50)
!241 = !DILocalVariable(name: "block", arg: 2, scope: !50, file: !1, line: 207, type: !53)
!242 = !DILocation(line: 207, column: 73, scope: !50)
!243 = !DILocalVariable(name: "block_size", arg: 3, scope: !50, file: !1, line: 207, type: !4)
!244 = !DILocation(line: 207, column: 87, scope: !50)
!245 = !DILocation(line: 210, column: 14, scope: !50)
!246 = !DILocation(line: 210, column: 2, scope: !50)
!247 = !DILocation(line: 210, column: 11, scope: !50)
!248 = !DILocation(line: 211, column: 14, scope: !50)
!249 = !DILocation(line: 211, column: 2, scope: !50)
!250 = !DILocation(line: 211, column: 11, scope: !50)
!251 = !DILocation(line: 212, column: 14, scope: !50)
!252 = !DILocation(line: 212, column: 2, scope: !50)
!253 = !DILocation(line: 212, column: 11, scope: !50)
!254 = !DILocation(line: 213, column: 14, scope: !50)
!255 = !DILocation(line: 213, column: 2, scope: !50)
!256 = !DILocation(line: 213, column: 11, scope: !50)
!257 = !DILocation(line: 214, column: 14, scope: !50)
!258 = !DILocation(line: 214, column: 2, scope: !50)
!259 = !DILocation(line: 214, column: 11, scope: !50)
!260 = !DILocation(line: 215, column: 14, scope: !50)
!261 = !DILocation(line: 215, column: 2, scope: !50)
!262 = !DILocation(line: 215, column: 11, scope: !50)
!263 = !DILocation(line: 216, column: 14, scope: !50)
!264 = !DILocation(line: 216, column: 2, scope: !50)
!265 = !DILocation(line: 216, column: 11, scope: !50)
!266 = !DILocation(line: 217, column: 14, scope: !50)
!267 = !DILocation(line: 217, column: 2, scope: !50)
!268 = !DILocation(line: 217, column: 11, scope: !50)
!269 = !DILocation(line: 218, column: 14, scope: !50)
!270 = !DILocation(line: 218, column: 2, scope: !50)
!271 = !DILocation(line: 218, column: 11, scope: !50)
!272 = !DILocation(line: 220, column: 6, scope: !273)
!273 = distinct !DILexicalBlock(scope: !50, file: !1, line: 220, column: 6)
!274 = !DILocation(line: 220, column: 17, scope: !273)
!275 = !DILocation(line: 220, column: 6, scope: !50)
!276 = !DILocation(line: 221, column: 15, scope: !277)
!277 = distinct !DILexicalBlock(scope: !273, file: !1, line: 220, column: 23)
!278 = !DILocation(line: 221, column: 3, scope: !277)
!279 = !DILocation(line: 221, column: 12, scope: !277)
!280 = !DILocation(line: 222, column: 15, scope: !277)
!281 = !DILocation(line: 222, column: 3, scope: !277)
!282 = !DILocation(line: 222, column: 12, scope: !277)
!283 = !DILocation(line: 223, column: 15, scope: !277)
!284 = !DILocation(line: 223, column: 3, scope: !277)
!285 = !DILocation(line: 223, column: 12, scope: !277)
!286 = !DILocation(line: 224, column: 15, scope: !277)
!287 = !DILocation(line: 224, column: 3, scope: !277)
!288 = !DILocation(line: 224, column: 12, scope: !277)
!289 = !DILocation(line: 226, column: 7, scope: !290)
!290 = distinct !DILexicalBlock(scope: !277, file: !1, line: 226, column: 7)
!291 = !DILocation(line: 226, column: 18, scope: !290)
!292 = !DILocation(line: 226, column: 7, scope: !277)
!293 = !DILocation(line: 227, column: 16, scope: !294)
!294 = distinct !DILexicalBlock(scope: !290, file: !1, line: 226, column: 25)
!295 = !DILocation(line: 227, column: 4, scope: !294)
!296 = !DILocation(line: 227, column: 13, scope: !294)
!297 = !DILocation(line: 228, column: 16, scope: !294)
!298 = !DILocation(line: 228, column: 4, scope: !294)
!299 = !DILocation(line: 228, column: 13, scope: !294)
!300 = !DILocation(line: 229, column: 16, scope: !294)
!301 = !DILocation(line: 229, column: 4, scope: !294)
!302 = !DILocation(line: 229, column: 13, scope: !294)
!303 = !DILocation(line: 230, column: 16, scope: !294)
!304 = !DILocation(line: 230, column: 4, scope: !294)
!305 = !DILocation(line: 230, column: 13, scope: !294)
!306 = !DILocation(line: 232, column: 8, scope: !307)
!307 = distinct !DILexicalBlock(scope: !294, file: !1, line: 232, column: 8)
!308 = !DILocation(line: 232, column: 19, scope: !307)
!309 = !DILocation(line: 232, column: 8, scope: !294)
!310 = !DILocation(line: 233, column: 17, scope: !311)
!311 = distinct !DILexicalBlock(scope: !307, file: !1, line: 232, column: 26)
!312 = !DILocation(line: 233, column: 5, scope: !311)
!313 = !DILocation(line: 233, column: 14, scope: !311)
!314 = !DILocation(line: 246, column: 4, scope: !311)
!315 = !DILocation(line: 247, column: 3, scope: !294)
!316 = !DILocation(line: 248, column: 2, scope: !277)
!317 = !DILocation(line: 250, column: 25, scope: !50)
!318 = !DILocation(line: 250, column: 2, scope: !50)
!319 = !DILocation(line: 251, column: 1, scope: !50)
!320 = !DILocalVariable(name: "ctx", arg: 1, scope: !43, file: !1, line: 308, type: !19)
!321 = !DILocation(line: 308, column: 33, scope: !43)
!322 = !DILocalVariable(name: "result", arg: 2, scope: !43, file: !1, line: 308, type: !46)
!323 = !DILocation(line: 308, column: 53, scope: !43)
!324 = !DILocalVariable(name: "digest_length", scope: !43, file: !1, line: 310, type: !4)
!325 = !DILocation(line: 310, column: 9, scope: !43)
!326 = !DILocation(line: 310, column: 31, scope: !43)
!327 = !DILocation(line: 310, column: 36, scope: !43)
!328 = !DILocation(line: 310, column: 47, scope: !43)
!329 = !DILocation(line: 310, column: 29, scope: !43)
!330 = !DILocation(line: 310, column: 25, scope: !43)
!331 = !DILocalVariable(name: "block_size", scope: !43, file: !1, line: 311, type: !332)
!332 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !4)
!333 = !DILocation(line: 311, column: 15, scope: !43)
!334 = !DILocation(line: 311, column: 28, scope: !43)
!335 = !DILocation(line: 311, column: 33, scope: !43)
!336 = !DILocation(line: 313, column: 8, scope: !337)
!337 = distinct !DILexicalBlock(scope: !43, file: !1, line: 313, column: 6)
!338 = !DILocation(line: 313, column: 13, scope: !337)
!339 = !DILocation(line: 313, column: 18, scope: !337)
!340 = !DILocation(line: 313, column: 6, scope: !43)
!341 = !DILocation(line: 316, column: 17, scope: !342)
!342 = distinct !DILexicalBlock(scope: !337, file: !1, line: 314, column: 2)
!343 = !DILocation(line: 316, column: 22, scope: !342)
!344 = !DILocation(line: 316, column: 10, scope: !342)
!345 = !DILocation(line: 316, column: 32, scope: !342)
!346 = !DILocation(line: 316, column: 37, scope: !342)
!347 = !DILocation(line: 316, column: 30, scope: !342)
!348 = !DILocation(line: 316, column: 46, scope: !342)
!349 = !DILocation(line: 316, column: 59, scope: !342)
!350 = !DILocation(line: 316, column: 64, scope: !342)
!351 = !DILocation(line: 316, column: 57, scope: !342)
!352 = !DILocation(line: 316, column: 3, scope: !342)
!353 = !DILocation(line: 317, column: 25, scope: !342)
!354 = !DILocation(line: 317, column: 30, scope: !342)
!355 = !DILocation(line: 317, column: 3, scope: !342)
!356 = !DILocation(line: 317, column: 11, scope: !342)
!357 = !DILocation(line: 317, column: 16, scope: !342)
!358 = !DILocation(line: 317, column: 36, scope: !342)
!359 = !DILocation(line: 318, column: 25, scope: !342)
!360 = !DILocation(line: 318, column: 36, scope: !342)
!361 = !DILocation(line: 318, column: 11, scope: !342)
!362 = !DILocation(line: 318, column: 16, scope: !342)
!363 = !DILocation(line: 318, column: 3, scope: !342)
!364 = !DILocation(line: 318, column: 41, scope: !342)
!365 = !DILocation(line: 321, column: 28, scope: !342)
!366 = !DILocation(line: 321, column: 33, scope: !342)
!367 = !DILocation(line: 321, column: 39, scope: !342)
!368 = !DILocation(line: 321, column: 44, scope: !342)
!369 = !DILocation(line: 321, column: 53, scope: !342)
!370 = !DILocation(line: 321, column: 3, scope: !342)
!371 = !DILocation(line: 322, column: 3, scope: !342)
!372 = !DILocation(line: 322, column: 8, scope: !342)
!373 = !DILocation(line: 322, column: 13, scope: !342)
!374 = !DILocation(line: 323, column: 2, scope: !342)
!375 = !DILocation(line: 325, column: 2, scope: !43)
!376 = !DILocation(line: 325, column: 2, scope: !377)
!377 = !DILexicalBlockFile(scope: !43, file: !1, discriminator: 1)
!378 = !DILocation(line: 325, column: 2, scope: !379)
!379 = !DILexicalBlockFile(scope: !43, file: !1, discriminator: 2)
!380 = !DILocation(line: 325, column: 2, scope: !381)
!381 = !DILexicalBlockFile(scope: !43, file: !1, discriminator: 3)
!382 = !DILocation(line: 326, column: 6, scope: !383)
!383 = distinct !DILexicalBlock(scope: !43, file: !1, line: 326, column: 6)
!384 = !DILocation(line: 326, column: 6, scope: !43)
!385 = !DILocation(line: 326, column: 14, scope: !386)
!386 = !DILexicalBlockFile(scope: !383, file: !1, discriminator: 1)
!387 = !DILocation(line: 327, column: 1, scope: !43)
!388 = !DILocalVariable(name: "state", arg: 1, scope: !55, file: !1, line: 159, type: !12)
!389 = !DILocation(line: 159, column: 46, scope: !55)
!390 = !DILocalVariable(name: "round", scope: !55, file: !1, line: 161, type: !391)
!391 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!392 = !DILocation(line: 161, column: 6, scope: !55)
!393 = !DILocation(line: 162, column: 13, scope: !394)
!394 = distinct !DILexicalBlock(scope: !55, file: !1, line: 162, column: 2)
!395 = !DILocation(line: 162, column: 7, scope: !394)
!396 = !DILocation(line: 162, column: 18, scope: !397)
!397 = !DILexicalBlockFile(scope: !398, file: !1, discriminator: 1)
!398 = distinct !DILexicalBlock(scope: !394, file: !1, line: 162, column: 2)
!399 = !DILocation(line: 162, column: 24, scope: !397)
!400 = !DILocation(line: 162, column: 2, scope: !397)
!401 = !DILocation(line: 164, column: 16, scope: !402)
!402 = distinct !DILexicalBlock(scope: !398, file: !1, line: 163, column: 2)
!403 = !DILocation(line: 164, column: 3, scope: !402)
!404 = !DILocation(line: 167, column: 15, scope: !402)
!405 = !DILocation(line: 167, column: 3, scope: !402)
!406 = !DILocation(line: 167, column: 13, scope: !402)
!407 = !DILocation(line: 168, column: 15, scope: !402)
!408 = !DILocation(line: 168, column: 3, scope: !402)
!409 = !DILocation(line: 168, column: 13, scope: !402)
!410 = !DILocation(line: 169, column: 15, scope: !402)
!411 = !DILocation(line: 169, column: 3, scope: !402)
!412 = !DILocation(line: 169, column: 13, scope: !402)
!413 = !DILocation(line: 170, column: 15, scope: !402)
!414 = !DILocation(line: 170, column: 3, scope: !402)
!415 = !DILocation(line: 170, column: 13, scope: !402)
!416 = !DILocation(line: 171, column: 15, scope: !402)
!417 = !DILocation(line: 171, column: 3, scope: !402)
!418 = !DILocation(line: 171, column: 13, scope: !402)
!419 = !DILocation(line: 172, column: 15, scope: !402)
!420 = !DILocation(line: 172, column: 3, scope: !402)
!421 = !DILocation(line: 172, column: 13, scope: !402)
!422 = !DILocation(line: 173, column: 15, scope: !402)
!423 = !DILocation(line: 173, column: 3, scope: !402)
!424 = !DILocation(line: 173, column: 13, scope: !402)
!425 = !DILocation(line: 174, column: 15, scope: !402)
!426 = !DILocation(line: 174, column: 3, scope: !402)
!427 = !DILocation(line: 174, column: 13, scope: !402)
!428 = !DILocation(line: 175, column: 15, scope: !402)
!429 = !DILocation(line: 175, column: 3, scope: !402)
!430 = !DILocation(line: 175, column: 13, scope: !402)
!431 = !DILocation(line: 176, column: 15, scope: !402)
!432 = !DILocation(line: 176, column: 3, scope: !402)
!433 = !DILocation(line: 176, column: 13, scope: !402)
!434 = !DILocation(line: 177, column: 15, scope: !402)
!435 = !DILocation(line: 177, column: 3, scope: !402)
!436 = !DILocation(line: 177, column: 13, scope: !402)
!437 = !DILocation(line: 178, column: 15, scope: !402)
!438 = !DILocation(line: 178, column: 3, scope: !402)
!439 = !DILocation(line: 178, column: 13, scope: !402)
!440 = !DILocation(line: 179, column: 15, scope: !402)
!441 = !DILocation(line: 179, column: 3, scope: !402)
!442 = !DILocation(line: 179, column: 13, scope: !402)
!443 = !DILocation(line: 180, column: 15, scope: !402)
!444 = !DILocation(line: 180, column: 3, scope: !402)
!445 = !DILocation(line: 180, column: 13, scope: !402)
!446 = !DILocation(line: 181, column: 15, scope: !402)
!447 = !DILocation(line: 181, column: 3, scope: !402)
!448 = !DILocation(line: 181, column: 13, scope: !402)
!449 = !DILocation(line: 182, column: 15, scope: !402)
!450 = !DILocation(line: 182, column: 3, scope: !402)
!451 = !DILocation(line: 182, column: 13, scope: !402)
!452 = !DILocation(line: 183, column: 15, scope: !402)
!453 = !DILocation(line: 183, column: 3, scope: !402)
!454 = !DILocation(line: 183, column: 13, scope: !402)
!455 = !DILocation(line: 184, column: 15, scope: !402)
!456 = !DILocation(line: 184, column: 3, scope: !402)
!457 = !DILocation(line: 184, column: 13, scope: !402)
!458 = !DILocation(line: 185, column: 15, scope: !402)
!459 = !DILocation(line: 185, column: 3, scope: !402)
!460 = !DILocation(line: 185, column: 13, scope: !402)
!461 = !DILocation(line: 186, column: 15, scope: !402)
!462 = !DILocation(line: 186, column: 3, scope: !402)
!463 = !DILocation(line: 186, column: 13, scope: !402)
!464 = !DILocation(line: 187, column: 15, scope: !402)
!465 = !DILocation(line: 187, column: 3, scope: !402)
!466 = !DILocation(line: 187, column: 13, scope: !402)
!467 = !DILocation(line: 188, column: 15, scope: !402)
!468 = !DILocation(line: 188, column: 3, scope: !402)
!469 = !DILocation(line: 188, column: 13, scope: !402)
!470 = !DILocation(line: 189, column: 15, scope: !402)
!471 = !DILocation(line: 189, column: 3, scope: !402)
!472 = !DILocation(line: 189, column: 13, scope: !402)
!473 = !DILocation(line: 190, column: 15, scope: !402)
!474 = !DILocation(line: 190, column: 3, scope: !402)
!475 = !DILocation(line: 190, column: 13, scope: !402)
!476 = !DILocation(line: 192, column: 13, scope: !402)
!477 = !DILocation(line: 192, column: 3, scope: !402)
!478 = !DILocation(line: 193, column: 14, scope: !402)
!479 = !DILocation(line: 193, column: 3, scope: !402)
!480 = !DILocation(line: 196, column: 36, scope: !402)
!481 = !DILocation(line: 196, column: 13, scope: !402)
!482 = !DILocation(line: 196, column: 4, scope: !402)
!483 = !DILocation(line: 196, column: 10, scope: !402)
!484 = !DILocation(line: 197, column: 2, scope: !402)
!485 = !DILocation(line: 162, column: 47, scope: !486)
!486 = !DILexicalBlockFile(scope: !398, file: !1, discriminator: 2)
!487 = !DILocation(line: 162, column: 2, scope: !486)
!488 = !DILocation(line: 198, column: 1, scope: !55)
!489 = !DILocalVariable(name: "A", arg: 1, scope: !58, file: !1, line: 90, type: !12)
!490 = !DILocation(line: 90, column: 36, scope: !58)
!491 = !DILocalVariable(name: "x", scope: !58, file: !1, line: 92, type: !7)
!492 = !DILocation(line: 92, column: 15, scope: !58)
!493 = !DILocalVariable(name: "C", scope: !58, file: !1, line: 93, type: !494)
!494 = !DICompositeType(tag: DW_TAG_array_type, baseType: !13, size: 320, align: 64, elements: !495)
!495 = !{!496}
!496 = !DISubrange(count: 5)
!497 = !DILocation(line: 93, column: 11, scope: !58)
!498 = !DILocalVariable(name: "D", scope: !58, file: !1, line: 93, type: !494)
!499 = !DILocation(line: 93, column: 17, scope: !58)
!500 = !DILocation(line: 95, column: 9, scope: !501)
!501 = distinct !DILexicalBlock(scope: !58, file: !1, line: 95, column: 2)
!502 = !DILocation(line: 95, column: 7, scope: !501)
!503 = !DILocation(line: 95, column: 14, scope: !504)
!504 = !DILexicalBlockFile(scope: !505, file: !1, discriminator: 1)
!505 = distinct !DILexicalBlock(scope: !501, file: !1, line: 95, column: 2)
!506 = !DILocation(line: 95, column: 16, scope: !504)
!507 = !DILocation(line: 95, column: 2, scope: !504)
!508 = !DILocation(line: 96, column: 12, scope: !509)
!509 = distinct !DILexicalBlock(scope: !505, file: !1, line: 95, column: 26)
!510 = !DILocation(line: 96, column: 10, scope: !509)
!511 = !DILocation(line: 96, column: 19, scope: !509)
!512 = !DILocation(line: 96, column: 21, scope: !509)
!513 = !DILocation(line: 96, column: 17, scope: !509)
!514 = !DILocation(line: 96, column: 15, scope: !509)
!515 = !DILocation(line: 96, column: 30, scope: !509)
!516 = !DILocation(line: 96, column: 32, scope: !509)
!517 = !DILocation(line: 96, column: 28, scope: !509)
!518 = !DILocation(line: 96, column: 26, scope: !509)
!519 = !DILocation(line: 96, column: 42, scope: !509)
!520 = !DILocation(line: 96, column: 44, scope: !509)
!521 = !DILocation(line: 96, column: 40, scope: !509)
!522 = !DILocation(line: 96, column: 38, scope: !509)
!523 = !DILocation(line: 96, column: 54, scope: !509)
!524 = !DILocation(line: 96, column: 56, scope: !509)
!525 = !DILocation(line: 96, column: 52, scope: !509)
!526 = !DILocation(line: 96, column: 50, scope: !509)
!527 = !DILocation(line: 96, column: 5, scope: !509)
!528 = !DILocation(line: 96, column: 3, scope: !509)
!529 = !DILocation(line: 96, column: 8, scope: !509)
!530 = !DILocation(line: 97, column: 2, scope: !509)
!531 = !DILocation(line: 95, column: 22, scope: !532)
!532 = !DILexicalBlockFile(scope: !505, file: !1, discriminator: 2)
!533 = !DILocation(line: 95, column: 2, scope: !532)
!534 = !DILocation(line: 98, column: 9, scope: !58)
!535 = !DILocation(line: 98, column: 27, scope: !58)
!536 = !DILocation(line: 98, column: 25, scope: !58)
!537 = !DILocation(line: 98, column: 2, scope: !58)
!538 = !DILocation(line: 98, column: 7, scope: !58)
!539 = !DILocation(line: 99, column: 9, scope: !58)
!540 = !DILocation(line: 99, column: 27, scope: !58)
!541 = !DILocation(line: 99, column: 25, scope: !58)
!542 = !DILocation(line: 99, column: 2, scope: !58)
!543 = !DILocation(line: 99, column: 7, scope: !58)
!544 = !DILocation(line: 100, column: 9, scope: !58)
!545 = !DILocation(line: 100, column: 27, scope: !58)
!546 = !DILocation(line: 100, column: 25, scope: !58)
!547 = !DILocation(line: 100, column: 2, scope: !58)
!548 = !DILocation(line: 100, column: 7, scope: !58)
!549 = !DILocation(line: 101, column: 9, scope: !58)
!550 = !DILocation(line: 101, column: 27, scope: !58)
!551 = !DILocation(line: 101, column: 25, scope: !58)
!552 = !DILocation(line: 101, column: 2, scope: !58)
!553 = !DILocation(line: 101, column: 7, scope: !58)
!554 = !DILocation(line: 102, column: 9, scope: !58)
!555 = !DILocation(line: 102, column: 27, scope: !58)
!556 = !DILocation(line: 102, column: 25, scope: !58)
!557 = !DILocation(line: 102, column: 2, scope: !58)
!558 = !DILocation(line: 102, column: 7, scope: !58)
!559 = !DILocation(line: 104, column: 9, scope: !560)
!560 = distinct !DILexicalBlock(scope: !58, file: !1, line: 104, column: 2)
!561 = !DILocation(line: 104, column: 7, scope: !560)
!562 = !DILocation(line: 104, column: 14, scope: !563)
!563 = !DILexicalBlockFile(scope: !564, file: !1, discriminator: 1)
!564 = distinct !DILexicalBlock(scope: !560, file: !1, line: 104, column: 2)
!565 = !DILocation(line: 104, column: 16, scope: !563)
!566 = !DILocation(line: 104, column: 2, scope: !563)
!567 = !DILocation(line: 105, column: 18, scope: !568)
!568 = distinct !DILexicalBlock(scope: !564, file: !1, line: 104, column: 26)
!569 = !DILocation(line: 105, column: 16, scope: !568)
!570 = !DILocation(line: 105, column: 5, scope: !568)
!571 = !DILocation(line: 105, column: 3, scope: !568)
!572 = !DILocation(line: 105, column: 13, scope: !568)
!573 = !DILocation(line: 106, column: 18, scope: !568)
!574 = !DILocation(line: 106, column: 16, scope: !568)
!575 = !DILocation(line: 106, column: 5, scope: !568)
!576 = !DILocation(line: 106, column: 7, scope: !568)
!577 = !DILocation(line: 106, column: 3, scope: !568)
!578 = !DILocation(line: 106, column: 13, scope: !568)
!579 = !DILocation(line: 107, column: 18, scope: !568)
!580 = !DILocation(line: 107, column: 16, scope: !568)
!581 = !DILocation(line: 107, column: 5, scope: !568)
!582 = !DILocation(line: 107, column: 7, scope: !568)
!583 = !DILocation(line: 107, column: 3, scope: !568)
!584 = !DILocation(line: 107, column: 13, scope: !568)
!585 = !DILocation(line: 108, column: 18, scope: !568)
!586 = !DILocation(line: 108, column: 16, scope: !568)
!587 = !DILocation(line: 108, column: 5, scope: !568)
!588 = !DILocation(line: 108, column: 7, scope: !568)
!589 = !DILocation(line: 108, column: 3, scope: !568)
!590 = !DILocation(line: 108, column: 13, scope: !568)
!591 = !DILocation(line: 109, column: 18, scope: !568)
!592 = !DILocation(line: 109, column: 16, scope: !568)
!593 = !DILocation(line: 109, column: 5, scope: !568)
!594 = !DILocation(line: 109, column: 7, scope: !568)
!595 = !DILocation(line: 109, column: 3, scope: !568)
!596 = !DILocation(line: 109, column: 13, scope: !568)
!597 = !DILocation(line: 110, column: 2, scope: !568)
!598 = !DILocation(line: 104, column: 22, scope: !599)
!599 = !DILexicalBlockFile(scope: !564, file: !1, discriminator: 2)
!600 = !DILocation(line: 104, column: 2, scope: !599)
!601 = !DILocation(line: 111, column: 1, scope: !58)
!602 = !DILocalVariable(name: "A", arg: 1, scope: !59, file: !1, line: 114, type: !12)
!603 = !DILocation(line: 114, column: 33, scope: !59)
!604 = !DILocalVariable(name: "A1", scope: !59, file: !1, line: 116, type: !13)
!605 = !DILocation(line: 116, column: 11, scope: !59)
!606 = !DILocation(line: 117, column: 7, scope: !59)
!607 = !DILocation(line: 117, column: 5, scope: !59)
!608 = !DILocation(line: 118, column: 10, scope: !59)
!609 = !DILocation(line: 118, column: 2, scope: !59)
!610 = !DILocation(line: 118, column: 8, scope: !59)
!611 = !DILocation(line: 119, column: 10, scope: !59)
!612 = !DILocation(line: 119, column: 2, scope: !59)
!613 = !DILocation(line: 119, column: 8, scope: !59)
!614 = !DILocation(line: 120, column: 10, scope: !59)
!615 = !DILocation(line: 120, column: 2, scope: !59)
!616 = !DILocation(line: 120, column: 8, scope: !59)
!617 = !DILocation(line: 121, column: 10, scope: !59)
!618 = !DILocation(line: 121, column: 2, scope: !59)
!619 = !DILocation(line: 121, column: 8, scope: !59)
!620 = !DILocation(line: 122, column: 10, scope: !59)
!621 = !DILocation(line: 122, column: 2, scope: !59)
!622 = !DILocation(line: 122, column: 8, scope: !59)
!623 = !DILocation(line: 123, column: 10, scope: !59)
!624 = !DILocation(line: 123, column: 2, scope: !59)
!625 = !DILocation(line: 123, column: 8, scope: !59)
!626 = !DILocation(line: 124, column: 10, scope: !59)
!627 = !DILocation(line: 124, column: 2, scope: !59)
!628 = !DILocation(line: 124, column: 8, scope: !59)
!629 = !DILocation(line: 125, column: 10, scope: !59)
!630 = !DILocation(line: 125, column: 2, scope: !59)
!631 = !DILocation(line: 125, column: 8, scope: !59)
!632 = !DILocation(line: 126, column: 10, scope: !59)
!633 = !DILocation(line: 126, column: 2, scope: !59)
!634 = !DILocation(line: 126, column: 8, scope: !59)
!635 = !DILocation(line: 127, column: 10, scope: !59)
!636 = !DILocation(line: 127, column: 2, scope: !59)
!637 = !DILocation(line: 127, column: 8, scope: !59)
!638 = !DILocation(line: 128, column: 10, scope: !59)
!639 = !DILocation(line: 128, column: 2, scope: !59)
!640 = !DILocation(line: 128, column: 8, scope: !59)
!641 = !DILocation(line: 129, column: 10, scope: !59)
!642 = !DILocation(line: 129, column: 2, scope: !59)
!643 = !DILocation(line: 129, column: 8, scope: !59)
!644 = !DILocation(line: 130, column: 10, scope: !59)
!645 = !DILocation(line: 130, column: 2, scope: !59)
!646 = !DILocation(line: 130, column: 8, scope: !59)
!647 = !DILocation(line: 131, column: 10, scope: !59)
!648 = !DILocation(line: 131, column: 2, scope: !59)
!649 = !DILocation(line: 131, column: 8, scope: !59)
!650 = !DILocation(line: 132, column: 10, scope: !59)
!651 = !DILocation(line: 132, column: 2, scope: !59)
!652 = !DILocation(line: 132, column: 8, scope: !59)
!653 = !DILocation(line: 133, column: 10, scope: !59)
!654 = !DILocation(line: 133, column: 2, scope: !59)
!655 = !DILocation(line: 133, column: 8, scope: !59)
!656 = !DILocation(line: 134, column: 10, scope: !59)
!657 = !DILocation(line: 134, column: 2, scope: !59)
!658 = !DILocation(line: 134, column: 8, scope: !59)
!659 = !DILocation(line: 135, column: 10, scope: !59)
!660 = !DILocation(line: 135, column: 2, scope: !59)
!661 = !DILocation(line: 135, column: 8, scope: !59)
!662 = !DILocation(line: 136, column: 10, scope: !59)
!663 = !DILocation(line: 136, column: 2, scope: !59)
!664 = !DILocation(line: 136, column: 8, scope: !59)
!665 = !DILocation(line: 137, column: 10, scope: !59)
!666 = !DILocation(line: 137, column: 2, scope: !59)
!667 = !DILocation(line: 137, column: 8, scope: !59)
!668 = !DILocation(line: 138, column: 10, scope: !59)
!669 = !DILocation(line: 138, column: 2, scope: !59)
!670 = !DILocation(line: 138, column: 8, scope: !59)
!671 = !DILocation(line: 139, column: 10, scope: !59)
!672 = !DILocation(line: 139, column: 2, scope: !59)
!673 = !DILocation(line: 139, column: 8, scope: !59)
!674 = !DILocation(line: 140, column: 10, scope: !59)
!675 = !DILocation(line: 140, column: 2, scope: !59)
!676 = !DILocation(line: 140, column: 8, scope: !59)
!677 = !DILocation(line: 141, column: 10, scope: !59)
!678 = !DILocation(line: 141, column: 2, scope: !59)
!679 = !DILocation(line: 141, column: 8, scope: !59)
!680 = !DILocation(line: 143, column: 1, scope: !59)
!681 = !DILocalVariable(name: "A", arg: 1, scope: !60, file: !1, line: 146, type: !12)
!682 = !DILocation(line: 146, column: 34, scope: !60)
!683 = !DILocalVariable(name: "i", scope: !60, file: !1, line: 148, type: !391)
!684 = !DILocation(line: 148, column: 6, scope: !60)
!685 = !DILocation(line: 149, column: 9, scope: !686)
!686 = distinct !DILexicalBlock(scope: !60, file: !1, line: 149, column: 2)
!687 = !DILocation(line: 149, column: 7, scope: !686)
!688 = !DILocation(line: 149, column: 14, scope: !689)
!689 = !DILexicalBlockFile(scope: !690, file: !1, discriminator: 1)
!690 = distinct !DILexicalBlock(scope: !686, file: !1, line: 149, column: 2)
!691 = !DILocation(line: 149, column: 16, scope: !689)
!692 = !DILocation(line: 149, column: 2, scope: !689)
!693 = !DILocalVariable(name: "A0", scope: !694, file: !1, line: 150, type: !13)
!694 = distinct !DILexicalBlock(scope: !690, file: !1, line: 149, column: 30)
!695 = !DILocation(line: 150, column: 12, scope: !694)
!696 = !DILocation(line: 150, column: 23, scope: !694)
!697 = !DILocation(line: 150, column: 21, scope: !694)
!698 = !DILocation(line: 150, column: 17, scope: !694)
!699 = !DILocalVariable(name: "A1", scope: !694, file: !1, line: 150, type: !13)
!700 = !DILocation(line: 150, column: 27, scope: !694)
!701 = !DILocation(line: 150, column: 38, scope: !694)
!702 = !DILocation(line: 150, column: 36, scope: !694)
!703 = !DILocation(line: 150, column: 32, scope: !694)
!704 = !DILocation(line: 151, column: 16, scope: !694)
!705 = !DILocation(line: 151, column: 15, scope: !694)
!706 = !DILocation(line: 151, column: 27, scope: !694)
!707 = !DILocation(line: 151, column: 25, scope: !694)
!708 = !DILocation(line: 151, column: 21, scope: !694)
!709 = !DILocation(line: 151, column: 19, scope: !694)
!710 = !DILocation(line: 151, column: 9, scope: !694)
!711 = !DILocation(line: 151, column: 7, scope: !694)
!712 = !DILocation(line: 151, column: 3, scope: !694)
!713 = !DILocation(line: 151, column: 12, scope: !694)
!714 = !DILocation(line: 152, column: 22, scope: !694)
!715 = !DILocation(line: 152, column: 20, scope: !694)
!716 = !DILocation(line: 152, column: 16, scope: !694)
!717 = !DILocation(line: 152, column: 15, scope: !694)
!718 = !DILocation(line: 152, column: 33, scope: !694)
!719 = !DILocation(line: 152, column: 31, scope: !694)
!720 = !DILocation(line: 152, column: 27, scope: !694)
!721 = !DILocation(line: 152, column: 25, scope: !694)
!722 = !DILocation(line: 152, column: 9, scope: !694)
!723 = !DILocation(line: 152, column: 7, scope: !694)
!724 = !DILocation(line: 152, column: 3, scope: !694)
!725 = !DILocation(line: 152, column: 12, scope: !694)
!726 = !DILocation(line: 153, column: 22, scope: !694)
!727 = !DILocation(line: 153, column: 20, scope: !694)
!728 = !DILocation(line: 153, column: 16, scope: !694)
!729 = !DILocation(line: 153, column: 15, scope: !694)
!730 = !DILocation(line: 153, column: 33, scope: !694)
!731 = !DILocation(line: 153, column: 31, scope: !694)
!732 = !DILocation(line: 153, column: 27, scope: !694)
!733 = !DILocation(line: 153, column: 25, scope: !694)
!734 = !DILocation(line: 153, column: 9, scope: !694)
!735 = !DILocation(line: 153, column: 7, scope: !694)
!736 = !DILocation(line: 153, column: 3, scope: !694)
!737 = !DILocation(line: 153, column: 12, scope: !694)
!738 = !DILocation(line: 154, column: 22, scope: !694)
!739 = !DILocation(line: 154, column: 20, scope: !694)
!740 = !DILocation(line: 154, column: 16, scope: !694)
!741 = !DILocation(line: 154, column: 15, scope: !694)
!742 = !DILocation(line: 154, column: 27, scope: !694)
!743 = !DILocation(line: 154, column: 25, scope: !694)
!744 = !DILocation(line: 154, column: 9, scope: !694)
!745 = !DILocation(line: 154, column: 7, scope: !694)
!746 = !DILocation(line: 154, column: 3, scope: !694)
!747 = !DILocation(line: 154, column: 12, scope: !694)
!748 = !DILocation(line: 155, column: 16, scope: !694)
!749 = !DILocation(line: 155, column: 15, scope: !694)
!750 = !DILocation(line: 155, column: 21, scope: !694)
!751 = !DILocation(line: 155, column: 19, scope: !694)
!752 = !DILocation(line: 155, column: 9, scope: !694)
!753 = !DILocation(line: 155, column: 7, scope: !694)
!754 = !DILocation(line: 155, column: 3, scope: !694)
!755 = !DILocation(line: 155, column: 12, scope: !694)
!756 = !DILocation(line: 156, column: 2, scope: !694)
!757 = !DILocation(line: 149, column: 24, scope: !758)
!758 = !DILexicalBlockFile(scope: !690, file: !1, discriminator: 2)
!759 = !DILocation(line: 149, column: 2, scope: !758)
!760 = !DILocation(line: 157, column: 1, scope: !60)
